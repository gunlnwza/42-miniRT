#!/bin/bash

TEST_FILE="tests/test_list.txt"
BIN="./miniRT"

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

i=1

while IFS="|" read -r filepath expected; do
    if [[ "$filepath" =~ ^# ]]; then
        echo -e "\n$filepath"
        continue
    fi

    if [[ -z "$filepath" ]]; then
        continue
    fi

    if [[ ! -f "tests/$filepath" ]]; then
        echo -e "$filepath ${RED}FILE NOT FOUND${NC}"
        continue
    fi

    output=$($BIN tests/"$filepath" --parse-only 2>&1)
    
    if echo "$output" | grep -q "$expected"; then
        echo -e "$i. $filepath ${GREEN}OK${NC}"
    else
        echo "------------------------------------------"
        echo -e "$i. $filepath ${RED}KO${NC}"
        echo -e "Expected:\n$expected"
        echo -e "Got:\n$output"
        echo "------------------------------------------"
    fi

    (( i++ ))
done < "$TEST_FILE"

echo
