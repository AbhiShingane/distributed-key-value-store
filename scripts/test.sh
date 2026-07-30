#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

BUILD_DIR="${PROJECT_ROOT}/build"

mkdir -p "${BUILD_DIR}"

cd "${BUILD_DIR}"

cmake ..

make -j

ctest --output-on-failure