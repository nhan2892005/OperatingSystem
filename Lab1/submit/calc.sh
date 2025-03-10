#!/bin/bash
declare -a HISTORY
LAST_ANS_FILE="cache.out"
LAST_ANS="0"

if [ -f "$LAST_ANS_FILE" ]; then
    LAST_ANS=$(cat "$LAST_ANS_FILE")
else
    LAST_ANS="0"
fi

while true; do
    # * USER INPUT
    read -p ">> " exp_str

    # * Process special commands
    case "$exp_str" in
        EXIT)
            exit 0
            ;;
        HIST)
            if [ ${#HISTORY[@]} -gt 5 ]; then
                for ((i=${#HISTORY[@]}-5; i<${#HISTORY[@]}; i++)); do
                    echo "${HISTORY[$i]}"
                done
            else
                for line in "${HISTORY[@]}"; do
                    echo "$line"
                done
            fi
            read -s
            clear
            continue
            ;;
    esac

    # Store input
    expr=$(echo "$exp_str" | sed "s/ANS/$LAST_ANS/g")

    # Validate equation
    if echo "$expr" | grep -q "[^0-9+*/%() -]"; then
        echo "SYNTAX ERROR"
        exit 1
    fi

    # Check if the operation contains '%'
    if echo "$expr" | grep -q "%"; then
        result=$(awk "BEGIN { print $expr }")
        echo "" > err.tmp
    else
        result=$(echo "scale=2; $expr" | bc 2>err.tmp | sed 's/\.00$//' | sed 's/^\.0*/0./')
    fi

    err=$(cat err.tmp)
    rm err.tmp

    # Check for errors
    if [[ -n "$err" ]]; then
        if echo "$err" | grep -qi "division by zero"; then
            echo "MATH ERROR"
        else
            echo "SYNTAX ERROR"
        fi
        read -s

        clear
        continue
    fi

    # Print the result
    echo "$result"

    # Save the last answer
    LAST_ANS="$result"
    echo "$LAST_ANS" > "$LAST_ANS_FILE"
    HISTORY+=("$exp_str = $result")

    read -s

    clear
done