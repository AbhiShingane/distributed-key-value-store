#!/bin/bash

set -e

############################################################
# Project Paths
############################################################

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

BUILD_DIR="${PROJECT_ROOT}/build"
DATA_DIR="${PROJECT_ROOT}/data"
LOG_DIR="${PROJECT_ROOT}/logs"

mkdir -p "${BUILD_DIR}"
mkdir -p "${LOG_DIR}"

############################################################
# Debug Mode
############################################################

if [ "$1" == "--debug" ]
then
    export KVSTORE_DEBUG=1
    shift
fi

############################################################
# Generate Log File
############################################################

TIMESTAMP=$(date +"%d%m%Y_%H%M%S")
LOG_FILE="${LOG_DIR}/report_${TIMESTAMP}.log"

# Save original stdout/stderr
exec 3>&1 4>&2

# Redirect everything to log file
exec >"${LOG_FILE}" 2>&1

############################################################
# Header
############################################################

echo "=========================================================="
echo "Distributed Key Value Store"
echo "Started : $(date)"
echo "Project : ${PROJECT_ROOT}"
echo "Log File: ${LOG_FILE}"
echo "=========================================================="

############################################################
# Build
############################################################

cd "${BUILD_DIR}"

echo
echo "Running CMake..."
cmake -G "Unix Makefiles" ..

echo
echo "Building..."
make -j

############################################################
# Prepare CSV Files
############################################################

FILES=""

for file in "$@"
do
    FILES="${FILES} ${DATA_DIR}/${file}"
done

echo
echo "Running with files:"
echo "${FILES}"
echo

############################################################
# Run Application
############################################################

./kvstore_app ${FILES}

############################################################
# Footer
############################################################

echo
echo "=========================================================="
echo "Finished : $(date)"
echo "=========================================================="

# Restore console
exec 1>&3 2>&4

echo
echo "Execution completed successfully."
echo "Log file:"
echo "${LOG_FILE}"