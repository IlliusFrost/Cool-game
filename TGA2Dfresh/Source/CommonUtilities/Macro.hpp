#pragma once
#include <assert.h>

#define MIN(a, b) ((a)<(b)?(a):(b))

#define MAX(a, b) ((a)>(b)?(a):(b))

#define SAFE_DELETE(ptr) \
delete ptr;				 \
ptr = nullptr;

#define CYCLIC_ERASE(vector, index) \
assert(index < vector.size() && index >= 0 && "Index out of bounds!"); \
vector[index] = vector[vector.size() - 1]; \
vector.pop_back();