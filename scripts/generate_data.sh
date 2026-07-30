#!/bin/bash

###############################################################################
# Distributed KV Store
# CSV Test Data Generator
###############################################################################

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DATA_DIR="${PROJECT_ROOT}/data"

mkdir -p "${DATA_DIR}"

echo "========================================================="
echo "        Distributed KV Store - CSV Generator"
echo "========================================================="
echo

read -p "Enter number of CSV files to generate: " TOTAL_FILES
echo

CURRENT_EMP_ID=1

for ((i=1; i<=TOTAL_FILES; i++))
do
    echo "---------------------------------------------------------"

    read -p "Enter file name (without .csv): " FILE_NAME

    read -p "Enter number of records: " RECORD_COUNT

    read -p "Generate duplicate records? (y/n): " DUPLICATE_OPTION

    DUPLICATE_COUNT=0

    if [[ "$DUPLICATE_OPTION" == "y" || "$DUPLICATE_OPTION" == "Y" ]]; then
        read -p "How many duplicate records?: " DUPLICATE_COUNT
    fi

    OUTPUT_FILE="${DATA_DIR}/${FILE_NAME}.csv"

    > "$OUTPUT_FILE"

    UNIQUE_COUNT=$((RECORD_COUNT - DUPLICATE_COUNT))

    declare -a GENERATED_RECORDS

    echo
    echo "Generating ${OUTPUT_FILE} ..."
    echo

    #########################################################
    # Generate unique records
    #########################################################

    for ((j=1; j<=UNIQUE_COUNT; j++))
    do
        EMP_ID=$(printf "EMP%04d" "$CURRENT_EMP_ID")

        AGE=$((20 + RANDOM % 41))
        SCORE=$((50 + RANDOM % 51))

        RECORD="${EMP_ID},${AGE},${SCORE}"

        GENERATED_RECORDS+=("$RECORD")

        echo "$RECORD" >> "$OUTPUT_FILE"

        CURRENT_EMP_ID=$((CURRENT_EMP_ID + 1))
    done

    #########################################################
    # Generate duplicates
    #########################################################

    if (( DUPLICATE_COUNT > 0 ))
    then
        echo "Adding ${DUPLICATE_COUNT} duplicate records..."

        for ((k=1; k<=DUPLICATE_COUNT; k++))
        do
            INDEX=$((RANDOM % UNIQUE_COUNT))

            echo "${GENERATED_RECORDS[$INDEX]}" >> "$OUTPUT_FILE"
        done
    fi

    echo
    echo "Created ${FILE_NAME}.csv"
    echo "Unique Records    : ${UNIQUE_COUNT}"
    echo "Duplicate Records : ${DUPLICATE_COUNT}"
    echo "Total Records     : ${RECORD_COUNT}"
    echo
done

echo "========================================================="
echo "CSV generation completed successfully."
echo "Files generated at:"
echo "${DATA_DIR}"
echo "========================================================="