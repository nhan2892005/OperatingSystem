#ifndef CALC_LOGIC_H
#define CALC_LOGIC_H

// Evaluates the arithmetic expression in 'expr' and stores the result in 'result'.
// If use_int_div is nonzero, divisions are performed as integer division.
// Returns 0 on success, 1 for syntax errors, and 2 for math errors (e.g. division by zero).
int eval_expr(const char* expr, double *result, int use_int_div);

#endif
