#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

BUILD_DIR="${PROJECT_ROOT}/build"

EXECUTABLE="${BUILD_DIR}/kvstore_app"

if [ ! -f "${EXECUTABLE}" ]; then
    echo "Executable not found."
    echo "Please run build.sh first."
    exit 1
fi

cd "${BUILD_DIR}"

echo "========================================="
echo "Running Distributed KV Store"
echo "========================================="

./kvstore_app