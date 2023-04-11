#pragma once

#include <stdio.h>

#define LOG(...) do { \
		fprintf(stderr, "%s:%i -- ", __FILE__, __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
} while(0)
