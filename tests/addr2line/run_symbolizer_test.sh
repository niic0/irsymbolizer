#!/bin/bash

# Skip 1 line (header)
skip_header=1
csv_file_line=0

# For each line in the csv
while IFS="," read -r module addr function file line label
do
    ((csv_file_line++))
    
    if [[ -z  $module || -z $addr || -z $function || -z $file || -z $line || -z $label ]]; then
       echo -e "\e[1m[TEST ERROR] One or more variables are undefined at line $csv_file_line"
       exit 1
    fi

    if ((skip_header)); then
	((skip_header--))
    else
	echo "$module | $addr | $function | $file | $line | $label"
	# Run ./IRSymbolizer --addr2line --addr <addr> --bin <binfile>
	# Compare output of the previous run with the 3 last elements of the csv
	# if good -> output good, if not -> not good
    fi
done < test_cases.csv
