#pragma once

#ifndef CROSS_PLATFORM_H
#define CROSS_PLATFORM_H

#ifdef _MSC_VER

#include <intrin.h>

// ===============================
// Visual Studio-specific settings
// ===============================

#ifndef __cplusplus
#define inline __inline
#endif
#define __func__ __FUNCTION__

#define R_OK 4

#define ftello(a)     _ftelli64(a)
#define fseeko(a,b,c) _fseeki64(a,b,c)

#define STDIN_FILENO _fileno(stdin)
#define STDOUT_FILENO _fileno(stdout)

#define u_int32_t uint32_t
#define ssize_t __int64

#if _MSC_VER < 1800
#define isnan _isnan
#endif

// POSIX deprecation
#define alloca _alloca
#define close _close
#define lseek _lseek
#define lseek64 _lseeki64
#define open _open
#define write _write

inline int __sync_fetch_and_add(int volatile* addr, int val)
{
	return (int)_InterlockedExchangeAdd64((__int64 volatile *)addr, val);
}

#endif

#endif
