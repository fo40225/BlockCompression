#include "Benchmark.h"
#include <sstream>
#include <iomanip>
#include "MemoryUtilities.h"

#ifdef _MSC_VER
#include "Windows.h"
#else
#include <time.h>
#endif

using namespace std;

#define NumSecondsInHour   3600.0
#define NumSecondsInMinute   60.0
#define BILLION               1E9

Benchmark::Benchmark() {
#ifdef _MSC_VER
	LARGE_INTEGER startingTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startingTime);
	_startTime = startingTime.QuadPart;
	_frequency = frequency.QuadPart;
#else
	struct timespec now;	
	clock_gettime(CLOCK_MONOTONIC, &now);
	_startTime = now.tv_sec;
	_frequency = now.tv_nsec;
#endif	
}

Benchmark::~Benchmark() {}

double Benchmark::GetElapsedSeconds(void) const {
#ifdef _MSC_VER	
	LARGE_INTEGER endingTime;
	QueryPerformanceCounter(&endingTime);
	int64_t elapsedTicks = endingTime.QuadPart - _startTime;
	return (double)elapsedTicks / (double)_frequency;
#else
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);	
	return (now.tv_sec - _startTime) + (now.tv_nsec - _frequency) / BILLION;
#endif	
}

string Benchmark::ConvertTime(double numSeconds) {

	stringstream ss;

	if (numSeconds > NumSecondsInHour)
	{
		double hours = numSeconds / NumSecondsInHour;
		ss << fixed << setprecision(3) << hours << " hrs";
		return ss.str();
	}

	if (numSeconds > NumSecondsInMinute)
	{
		double minutes = numSeconds / NumSecondsInMinute;
		ss << fixed << setprecision(2) << minutes << " min";
		return ss.str();
	}

	ss << fixed << setprecision(2) << numSeconds << " s";
	return ss.str();
}

string Benchmark::ConvertSpeed(double speed) {
	stringstream ss;
	ss << MemoryUtilities::ToHumanReadable((int64_t)speed) << "/s";
	return ss.str();
}
