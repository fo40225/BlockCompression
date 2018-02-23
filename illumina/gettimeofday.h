#pragma once

#include <time.h>
#include <winsock2.h>

#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64

struct timezone
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
