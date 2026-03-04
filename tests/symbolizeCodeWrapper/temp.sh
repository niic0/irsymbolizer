#!/bin/bash

for BIN in test/inputs/*; do
    BIN_NAME=$(basename "$BIN")
    for addr in $(objdump -d "$BIN" | awk '/^[[:xdigit:]]+:/ { print $1 }'); do
        ./build/IRSymbolizer "$BIN" "$addr"
    done > "test/expected/$BIN_NAME.out"
done
