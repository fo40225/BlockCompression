#pragma once

#include <string>
#include <vector>
#include "TimingResult.h"
#include "MeanStdDev.h"
#include "BenchmarkResult.h"

class BenchmarkStatistics {
public:
	BenchmarkStatistics();
	~BenchmarkStatistics();
	void AddTimingData(const std::string description, const int compressionLevel,
		const int blockSize, const std::vector<TimingResult>& results);
	void Display(void);
	void DisplayHeader(void);

private:
	std::vector<BenchmarkResult> _benchmarkResults;
	MeanStdDev CalculateMeanStdDev(const std::vector<TimingResult>& results);
	int GetMaxFieldSize(const size_t fieldSize, int maxSize);
	void DisplayField(const std::string& field, const int fieldSize, const char leftSpace, const char rightSpace);
	double CalculateWeissmanScore(double baselineCompressionRatio, double baselineSeconds, double compressionRatio, double seconds);
	double GetTimeScalingFactor(void);
	void SetMinFieldLengths(void);
	void SetRankAndScale(void);
	int _algorithmLen;
	int _totalTimeLen;
	int _compSpeedLen;
	int _compSpeedStdDevLen;
	int _decompSpeedLen;
	int _decompSpeedStdDevLen;
};

