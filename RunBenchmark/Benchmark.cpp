#include "Benchmark.h"
#include <sstream>
#include <iomanip>
#include "Windows.h"
#include "MemoryUtilities.h"

using namespace std;

Benchmark::Benchmark() {
	LARGE_INTEGER startingTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startingTime);
	_startTime = startingTime.QuadPart;
	_frequency = frequency.QuadPart;
}

Benchmark::~Benchmark() {}

double Benchmark::GetElapsedSeconds(void) const {
	LARGE_INTEGER endingTime;
	QueryPerformanceCounter(&endingTime);
	int64_t elapsedTicks = endingTime.QuadPart - _startTime;
	return (double)elapsedTicks / (double)_frequency;
}

string Benchmark::ConvertElapsedTime(double numSeconds) {
	stringstream ss;
	ss << fixed << setprecision(7) << numSeconds << " s";
	return ss.str();
}

string Benchmark::ConvertSpeed(double speed) {
	stringstream ss;
	ss << MemoryUtilities::ToHumanReadable((int64_t)speed) << "/s";
	return ss.str();
}