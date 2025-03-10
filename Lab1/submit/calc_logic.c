#include "calc_logic.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

static const char *p; // current position in expression
static int error;
static int math_error;

static void skip_whitespace(void) {
    while (*p && isspace((unsigned char)*p))
        p++;
}

static double parse_expr(int use_int_div);
static double parse_term(int use_int_div);
static double parse_factor(int use_int_div);

static double parse_expr(int use_int_div) {
    double left = parse_term(use_int_div);
    skip_whitespace();
    while (*p == '+' || *p == '-') {
        char op = *p;
        p++;
        double right = parse_term(use_int_div);
        if (op == '+')
            left += right;
        else
            left -= right;
        skip_whitespace();
    }
    return left;
}

static double parse_term(int use_int_div) {
    double left = parse_factor(use_int_div);
    skip_whitespace();
    while (*p == '*' || *p == '/' || *p == '%') {
        char op = *p;
        p++;
        double right = parse_factor(use_int_div);
        skip_whitespace();
        if (op == '/') {
            if (right == 0) {
                math_error = 1;
                return 0;
            }
            if (use_int_div) {
                left = (int)left / (int)right;
            } else {
                left /= right;
            }
        } else if (op == '*') {
            left *= right;
        } else if (op == '%') {
            if (right == 0) {
                math_error = 1;
                return 0;
            }
            left = (int)left % (int)right;
        }
    }
    return left;
}

static double parse_factor(int use_int_div) {
    skip_whitespace();
    double result = 0;
    if (*p == '(') {
        p++; // skip '('
        result = parse_expr(use_int_div);
        skip_whitespace();
        if (*p == ')') {
            p++; // skip ')'
        } else {
            error = 1;
        }
    } else if (*p == '-') {  // unary minus
        p++;
        result = -parse_factor(use_int_div);
    } else {
        char *endptr;
        result = strtod(p, &endptr);
        if (p == endptr) {
            error = 1;
            return 0;
        }
        p = endptr;
    }
    skip_whitespace();
    return result;
}

int eval_expr(const char* expr, double *result, int use_int_div) {
    p = expr;
    error = 0;
    math_error = 0;
    double res = parse_expr(use_int_div);
    skip_whitespace();
    if (*p != '\0') {
        error = 1;
    }
    if (math_error)
        return 2;
    if (error)
        return 1;
    *result = res;
    return 0;
}
