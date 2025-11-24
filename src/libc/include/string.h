#pragma once

#include <stddef.h>

void* memset(void* dst, int value, size_t size);
int strcmp (const char*, const char*);
int strncmp (const char*, const char*, size_t);
size_t strlen(const char*);