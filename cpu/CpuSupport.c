#include "CpuSupport.h"

#ifdef _MSC_VER

#include <intrin.h>
#define CPUID(info, x) __cpuidex(info, x, 0)

#else

#include <cpuid.h>
#define CPUID(info, x) __cpuid_count(x, 0, info[0], info[1], info[2], info[3])

#endif

// returns true if this CPU has AVX support
int HasAvx() {
	unsigned int cpuInfo[4];
	CPUID(cpuInfo, 0x00000001);
	return cpuInfo[2] & 1 << 28 ? 1 : 0;
}
