#pragma once

#ifdef _WIN32

#include <intrin.h>
#define CPUID(info, x) __cpuidex(info, x, 0)

#else

#include <cpuid.h>
#define CPUID(info, x) __cpuid_count(x, 0, info[0], info[1], info[2], info[3])

#endif

// check for AVX support
int HasAvx(void);
