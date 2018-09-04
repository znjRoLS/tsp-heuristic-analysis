#pragma once

#include <cmath>

#define EPSILON 10e-9
#define DOUBLE_EQUAL(x, y) (fabs(x-y) < EPSILON)
#define DOUBLE_LESS(x, y) (!DOUBLE_EQUAL(x,y) && x < y)
#define DOUBLE_GREATER(x, y) (!DOUBLE_EQUAL(x,y) && x > y)
#define DOUBLE_LESS_OR_EQUAL(x, y) (!DOUBLE_GREATER(x,y))
#define DOUBLE_GREATER_OR_EQUAL(x, y) (!DOUBLE_LESS(x,y))