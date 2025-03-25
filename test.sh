#!/bin/bash

TEST_FILE="tests/test_list.txt"
BIN="./miniRT"

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

if [[ $1 == "--verbose" ]]; then
    VERBOSE=1
else
    VERBOSE=0
fi

i=1
OK=0
KO=0

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
        (( OK++ ))
        echo -e "$i. $filepath ${GREEN}OK${NC}"
        if [[ $VERBOSE -eq 1 ]]; then
            echo -e "$output"
            echo "------------------------------------------"
        fi
    else
        (( KO++ ))
        echo -e "$i. $filepath ${RED}KO${NC}"
        echo -e "Expected:\n$expected"
        echo -e "Got:\n$output"
        echo "------------------------------------------"
    fi

    (( i++ ))
done < "$TEST_FILE"

echo
echo -e "${GREEN}OK${NC}: $OK"
echo -e "${RED}KO${NC}: $KO"
echo
