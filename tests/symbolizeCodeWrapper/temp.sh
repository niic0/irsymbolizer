#!/bin/bash

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <binary>"
  exit 1
fi

binary=$1
output=$(mktemp)
objdump -Sl -d "$binary" > "$output"

echo "🔍 Analyzing '$binary' for signs of inlining and loop unrolling..."

# Inlining: Look for multiple symbols with same file/line number
echo -e "\n===== 🔁 Potential Inlining Sites ====="
grep -P '^\S.*\s+<.*>:$' "$output" | awk '
  {
    line=$0
    if (match(line, /([^:]+):([0-9]+)\s+<(.+)>:/, arr)) {
      loc = arr[1] ":" arr[2]
      sym[loc] = sym[loc] "," arr[3]
      count[loc]++
    }
  }
  END {
    for (l in count) {
      if (count[l] > 1) {
        printf "[%s] → %d overlapping functions:%s\n", l, count[l], sym[l]
      }
    }
  }
'

# Loop unrolling: Look for same instruction repeated in tight spans
echo -e "\n===== 🔂 Potential Loop Unrolling Sites ====="
awk '
  /^[[:xdigit:]]+:/ {
    inst = $0
    gsub(/^[[:xdigit:]]+:\s+/, "", inst)
    if (inst == last_inst) {
      repeat++
    } else {
      if (repeat >= 2) {
        print "Unrolled loop pattern near:", last_line
      }
      repeat = 0
    }
    last_inst = inst
    last_line = $0
  }
' "$output"
