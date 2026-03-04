#!/bin/bash

set -e

SYMBOLIZER=$1
INPUT_DIR=$2
EXPECTED_DIR=$3

for BIN in "$INPUT_DIR"/*; do
    BIN_NAME=$(basename "$BIN")
    echo "Testing $BIN_NAME..."

    # Obtain addresses from binary
    OUTPUT=$(mktemp)
    for addr in $(objdump -d "$BIN" | awk '/^[[:xdigit:]]+:/ { print $1 }'); do
        $SYMBOLIZER --bin "$BIN" --addr "$addr" >> "$OUTPUT"
    done

    diff -u "$EXPECTED_DIR/$BIN_NAME.out" "$OUTPUT" || {
        echo "Mismatch for $BIN_NAME"
        exit 1
    }
    echo "✔ Passed $BIN_NAME"
    rm "$OUTPUT"
done
