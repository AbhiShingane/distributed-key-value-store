#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"
DATA_DIR="${PROJECT_ROOT}/data"

mkdir -p "${BUILD_DIR}"

cd "${BUILD_DIR}"

cmake -G "Unix Makefiles" ..

make -j

if [ "$1" == "--debug" ]
then
    export KVSTORE_DEBUG=1
    shift
fi

FILES=""

for file in "$@"
do
    FILES="${FILES} ${DATA_DIR}/${file}"
done

echo
echo "Running with files:"
echo "${FILES}"
echo

./kvstore_app ${FILES}