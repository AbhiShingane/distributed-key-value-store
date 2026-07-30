#!/bin/bash

set -e

# Project root directory
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

BUILD_DIR="${PROJECT_ROOT}/build"

echo "========================================="
echo "Building Distributed KV Store"
echo "Project Root : ${PROJECT_ROOT}"
echo "Build Folder : ${BUILD_DIR}"
echo "========================================="

mkdir -p "${BUILD_DIR}"

cd "${BUILD_DIR}"

echo "Running CMake..."

cmake -G "Unix Makefiles" ..

echo ""
echo "Building..."

make -j"$(nproc)"

echo ""
echo "========================================="
echo "Build completed successfully."
echo "========================================="