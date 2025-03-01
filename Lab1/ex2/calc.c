#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc_logic.h"

#define MAX_LINE 1024

// Trim leading and trailing whitespace in place.
void trim(char *s) {
    char *start = s;
    while(*start && isspace((unsigned char)*start))
        start++;
    if(start != s)
        memmove(s, start, strlen(start) + 1);
    int len = strlen(s);
    while(len > 0 && isspace((unsigned char)s[len-1])) {
        s[len-1] = '\0';
        len--;
    }
}

// Replace every occurrence of "ANS" in input with the string last_ans_str.
// Returns a newly allocated string (caller must free it).
char *replace_ans(const char *input, const char *last_ans_str) {
    size_t token_len = 3; // length of "ANS"
    size_t rep_len = strlen(last_ans_str);
    size_t bufsize = strlen(input) + 1;
    // A rough overestimate: if many occurrences occur, we might need extra space.
    bufsize += 100;
    char *result = malloc(bufsize);
    if (!result) return NULL;
    result[0] = '\0';

    const char *p = input;
    while (*p) {
        if (strncmp(p, "ANS", 3) == 0) {
            strcat(result, last_ans_str);
            p += 3;
        } else {
            size_t len = strlen(result);
            result[len] = *p;
            result[len+1] = '\0';
            p++;
        }
    }
    return result;
}

// A simple case-sensitive string comparison.
int equals(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

int main(void) {
    char line[MAX_LINE];
    double last_ans = 0.0;
    int has_last_ans = 0; // flag: if a previous answer exists

    while (1) {
        printf(">> ");
        fflush(stdout);
        if (!fgets(line, MAX_LINE, stdin))
            break; // EOF

        // Remove trailing newline.
        line[strcspn(line, "\n")] = '\0';
        trim(line);
        if (strlen(line) == 0)
            continue;

        // Process special commands.
        if (equals(line, "EXIT")) {
            break;
        } else if (equals(line, "CLEAR")) {
            last_ans = 0.0;
            has_last_ans = 0;
            printf("MEMORY WAS CLEARED.\n");
            continue;
        }

        // If the input contains "ANS" but no previous answer exists.
        char *processed = NULL;
        if (strstr(line, "ANS") != NULL) {
            if (!has_last_ans) {
                printf("DO NOT HAVE EXPRESSION BEFORE\n");
                continue;
            }
            char last_ans_str[64];
            if (last_ans == (int)last_ans)
                sprintf(last_ans_str, "%d", (int)last_ans);
            else
                sprintf(last_ans_str, "%.2f", last_ans);
            processed = replace_ans(line, last_ans_str);
        } else {
            processed = strdup(line);
        }
        if (!processed)
            continue;

        // Validate: allow only digits, whitespace, parentheses, and operators +, -, *, /, %, and dot.
        int valid = 1;
        for (char *p = processed; *p; p++) {
            if (!(isdigit((unsigned char)*p) || isspace((unsigned char)*p) ||
                  strchr("+-*/%.()", *p))) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("SYNTAX ERROR\n");
            free(processed);
            continue;
        }

        // Check for integer division operator: if original input contains "//", then set flag.
        int use_int_div = 0;
        if (strstr(line, "//") != NULL) {
            use_int_div = 1;
            // Replace every occurrence of "//" with "/" in the processed expression.
            char *temp = malloc(strlen(processed) + 1);
            if (temp) {
                char *src = processed, *dst = temp;
                while (*src) {
                    if (src[0]=='/' && src[1]=='/') {
                        *dst++ = '/';
                        src += 2;
                    } else {
                        *dst++ = *src++;
                    }
                }
                *dst = '\0';
                free(processed);
                processed = temp;
            }
        }

        double result = 0.0;
        int status = eval_expr(processed, &result, use_int_div);
        free(processed);

        if (status == 1) {
            printf("SYNTAX ERROR\n");
            continue;
        } else if (status == 2) {
            printf("MATH ERROR\n");
            continue;
        }

        // Output result: if it is an integer value, print as integer.
        if (result == (int)result)
            printf("%d\n", (int)result);
        else
            printf("%.2f\n", result);
        last_ans = result;
        has_last_ans = 1;
    }
    return 0;
}
