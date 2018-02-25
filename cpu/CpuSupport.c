#include "CpuSupport.h"

// returns true if this CPU has AVX support
int HasAvx(void) {
	unsigned int cpuInfo[4];
	CPUID(cpuInfo, 0x00000001);
	return cpuInfo[2] & 1 << 28 ? 1 : 0;
}
