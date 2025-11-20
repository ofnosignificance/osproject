#pragma once

#include <stddef.h>

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
size_t strlen(const char* str);
