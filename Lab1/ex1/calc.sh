#!/bin/bash

declare -a HISTORY
LAST_ANS=""

while true; do
    # * USER INPUT
    read -p ">> " exp_str

    # * Normalize the expression
    exp_str=$(echo "$exp_str" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    exp_str=$(echo "$exp_str" | sed -E 's/ +/ /g; s/\( +/(/g; s/ +\)/)/g')
    # echo "$exp_str" >> history.txt

    # * Process special commands
    case "$exp_str" in
        EXIT)
            exit 0
            ;;
        HIST)
            if [ ${#HISTORY[@]} -eq 0 ]; then
                echo "No history yet."
            else
                for line in "${HISTORY[@]}"; do
                    echo "$line"
                done
            fi
            continue
            ;;
        CLEAR)
            HISTORY=()
            LAST_ANS=""
            read -n 1 -s -r -p "MEMORY WAS CLEARED. Press any key to continue..."
            clear
            continue
            ;;
    esac

    # * Use ANS but memory is empty
    if [[ "$exp_str" == *"ANS"* ]] && [ -z "$LAST_ANS" ]; then
        echo "DO NOT HAVE EXPRESSION BEFORE"
        continue
    fi

    # * Replace ANS with the last answer
    expr=$(echo "$exp_str" | sed "s/ANS/$LAST_ANS/g")

    # * Validate the substituted expression
    # Allow only digits, whitespace, parentheses, and the operators: +, -, *, /, %, and dot.
    if echo "$expr" | grep -q "[^0-9+*/%. ()-]"; then
        echo "SYNTAX ERROR"
        continue
    fi

    # Evaluate the expression
    if echo "$expr" | grep -q "//"; then
        eval_expr=$(echo "$expr" | sed 's|//|/|g')
        result=$(echo "scale=0; $eval_expr" | bc 2>err.tmp)
    else
        eval_expr="$expr"
        result=$(echo "scale=2; $eval_expr" | bc 2>err.tmp | sed 's/\.00$//')
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
        continue
    fi

    # Print the result
    echo "$result"
    LAST_ANS="$result"                  # Save the result to the memory
    HISTORY+=("$exp_str = $result")     # Save the expression and the result to the history  
done
