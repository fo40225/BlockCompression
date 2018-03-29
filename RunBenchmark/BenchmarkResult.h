#pragma once

#include <string>
#include "MeanStdDev.h"
#include "Benchmark.h"

class BenchmarkResult {
public:
	BenchmarkResult(std::string description, const int compressionLevel, const int blockSize, const MeanStdDev& msd, const int dataLen)
		: Description(description)
		, CompressionLevel(compressionLevel)
		, BlockSize(blockSize)
		, CompressionRatioMean(msd.CompressionRatioMean)
		, CompressionSpeedMean(msd.CompressionSpeedMean)
		, DecompressionSpeedMean(msd.DecompressionSpeedMean)
		, CompressionSpeedStdDev(msd.CompressionSpeedStdDev)
		, DecompressionSpeedStdDev(msd.DecompressionSpeedStdDev)
		, NumCompressionSeconds(msd.NumCompressionSecondsMean)
		, NumDecompressionSeconds(msd.NumDecompressionSecondsMean)
		, CompressionSpeedMeanString(Benchmark::ConvertSpeed(msd.CompressionSpeedMean))
		, DecompressionSpeedMeanString(Benchmark::ConvertSpeed(msd.DecompressionSpeedMean))
		, CompressionSpeedStdDevString(Benchmark::ConvertSpeed(msd.CompressionSpeedStdDev))
		, DecompressionSpeedStdDevString(Benchmark::ConvertSpeed(msd.DecompressionSpeedStdDev))
		, TotalTimeString(Benchmark::ConvertTime(msd.NumCompressionSecondsMean + msd.NumDecompressionSecondsMean))
		, SpeedScale(0.0)
		, CompressionRatioScale(0.0)
		, SpeedRank(0)
		, CompressionRatioRank(0)
	{
		double numTotalSeconds = NumCompressionSeconds + NumDecompressionSeconds;
		TotalSpeed             = dataLen / numTotalSeconds;
		TotalTimeString        = Benchmark::ConvertTime(numTotalSeconds);
	}

	~BenchmarkResult() {}

	std::string Description;
	int CompressionLevel;
	int BlockSize;

	double NumCompressionSeconds;
	double NumDecompressionSeconds;
	double TotalSpeed;

	double CompressionRatioMean;
	double CompressionSpeedMean;
	double DecompressionSpeedMean;
	double CompressionSpeedStdDev;
	double DecompressionSpeedStdDev;
	
	double SpeedScale;
	double CompressionRatioScale;

	int SpeedRank;
	int CompressionRatioRank;

	std::string CompressionSpeedMeanString;
	std::string DecompressionSpeedMeanString;
	std::string CompressionSpeedStdDevString;
	std::string DecompressionSpeedStdDevString;
	std::string TotalTimeString;
};
