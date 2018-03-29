#include "BenchmarkStatistics.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Benchmark.h"

using namespace std;

BenchmarkStatistics::BenchmarkStatistics() {}
BenchmarkStatistics::~BenchmarkStatistics() {}

#define CL_LEN        2
#define BLOCKSIZE_LEN 9
#define COMPRATIO_LEN 9
#define SCALE_LEN     6
#define RANK_LEN      6

void BenchmarkStatistics::DisplayHeader(void) {

	SetMinFieldLengths();
	SetRankAndScale();

	DisplayField("Algorithm", _algorithmLen,       '\0', ' ');
	DisplayField("CL", CL_LEN,                     ' ', ' ');
	DisplayField("TotalTime", _totalTimeLen,       ' ', ' ');
	DisplayField("CompRatio", COMPRATIO_LEN,       ' ', ' ');
	DisplayField("CompSpeed", _compSpeedLen,       ' ', ' ');
	DisplayField("DecompSpeed", _decompSpeedLen,   ' ', ' ');
	DisplayField("Speed%", SCALE_LEN,              ' ', ' ');
	DisplayField("Ratio%", SCALE_LEN,              ' ', ' ');
	DisplayField("SpRank", RANK_LEN,               ' ', ' ');
	DisplayField("CrRank", RANK_LEN,               ' ', ' ');
	cout << endl;

	cout << setfill('-');
	DisplayField("-", _algorithmLen,   '\0', ':');
	DisplayField("-", CL_LEN,          '-', ':');
	DisplayField("-", _totalTimeLen,   '-', ':');
	DisplayField("-", COMPRATIO_LEN,   '-', ':');
	DisplayField("-", _compSpeedLen,   '-', ':');
	DisplayField("-", _decompSpeedLen, '-', ':');
	DisplayField("-", SCALE_LEN,       '-', ':');
	DisplayField("-", SCALE_LEN,       '-', ':');
	DisplayField("-", RANK_LEN,        '-', ':');
	DisplayField("-", RANK_LEN,        '-', ':');
	cout << setfill(' ') << endl;
}

struct OrderByTotalSpeed
{
	bool operator()(BenchmarkResult* const &i, BenchmarkResult* const &j) const { 
		return i->TotalSpeed > j->TotalSpeed;
	}
};

struct OrderByCompressionRatio
{
	bool operator()(BenchmarkResult* const &i, BenchmarkResult* const &j) const {
		return i->CompressionRatioMean > j->CompressionRatioMean;
	}
};


void BenchmarkStatistics::SetRankAndScale(void) {

	vector<BenchmarkResult*> tempResults;
	for (auto it = _benchmarkResults.begin(); it != _benchmarkResults.end(); ++it) tempResults.push_back(&(*it));

	sort(tempResults.begin(), tempResults.end(), OrderByTotalSpeed());

	int index = 1;
	for (auto it = tempResults.begin(); it != tempResults.end(); ++it, index++) {
		(*it)->SpeedRank = index;
	}

	sort(tempResults.begin(), tempResults.end(), OrderByCompressionRatio());

	index = 1;
	for (auto it = tempResults.begin(); it != tempResults.end(); ++it, index++) {
		(*it)->CompressionRatioRank = index;
	}

	const double baselineSpeed            = _benchmarkResults[0].TotalSpeed;
	const double baselineCompressionRatio = _benchmarkResults[0].CompressionRatioMean;

	for (auto it = _benchmarkResults.begin(); it != _benchmarkResults.end(); ++it) {
		it->SpeedScale            = it->TotalSpeed / baselineSpeed;
		it->CompressionRatioScale = it->CompressionRatioMean / baselineCompressionRatio;
	}
}

void BenchmarkStatistics::DisplayField(const string& field, const int fieldSize, const char leftSpace, const char rightSpace) {
	if (leftSpace != 0) cout << leftSpace;
	cout << setw(fieldSize) << field << rightSpace << "|";
}

void BenchmarkStatistics::SetMinFieldLengths(void) {

	_algorithmLen         = 9;
	_totalTimeLen         = 9;
	_compSpeedLen         = 9;
	_compSpeedStdDevLen   = 11;
	_decompSpeedLen       = 11;
	_decompSpeedStdDevLen = 13;

	for (auto it = _benchmarkResults.begin(); it != _benchmarkResults.end(); ++it) {
		_algorithmLen         = GetMaxFieldSize(it->Description.size(),                    _algorithmLen);
		_totalTimeLen         = GetMaxFieldSize(it->TotalTimeString.size(),                _totalTimeLen);
		_compSpeedLen         = GetMaxFieldSize(it->CompressionSpeedMeanString.size(),     _compSpeedLen);
		_compSpeedStdDevLen   = GetMaxFieldSize(it->CompressionSpeedStdDevString.size(),   _compSpeedStdDevLen);
		_decompSpeedLen       = GetMaxFieldSize(it->DecompressionSpeedMeanString.size(),   _decompSpeedLen);
		_decompSpeedStdDevLen = GetMaxFieldSize(it->DecompressionSpeedStdDevString.size(), _decompSpeedStdDevLen);
	}
}

int BenchmarkStatistics::GetMaxFieldSize(const size_t fieldSize, int maxSize) {
	if (fieldSize > maxSize) maxSize = (int)fieldSize;
	return maxSize;
}

void BenchmarkStatistics::Display(void) {

	for (auto it = _benchmarkResults.begin(); it != _benchmarkResults.end(); ++it) {
		cout << left;
		DisplayField(it->Description, _algorithmLen, '\0', ' ');
		cout << right;
		cout << " " << setw(CL_LEN) << it->CompressionLevel << " |";
		DisplayField(it->TotalTimeString, _totalTimeLen,                        ' ', ' ');
		cout << " " << fixed << setw(COMPRATIO_LEN) << setprecision(2) << it->CompressionRatioMean << " |";
		DisplayField(it->CompressionSpeedMeanString, _compSpeedLen,             ' ', ' ');
		DisplayField(it->DecompressionSpeedMeanString, _decompSpeedLen,         ' ', ' ');
		cout << " " << fixed << setw(SCALE_LEN) << setprecision(3) << it->SpeedScale << " |";
		cout << " " << fixed << setw(SCALE_LEN) << setprecision(3) << it->CompressionRatioScale << " |";
		cout << " " << setw(RANK_LEN) << it->SpeedRank << " |";
		cout << " " << setw(RANK_LEN) << it->CompressionRatioRank << " |";
		cout << endl;
	}
}

void BenchmarkStatistics::AddTimingData(const string description, const int compressionLevel,
	const int blockSize, const vector<TimingResult>& results) {

	auto msd = CalculateMeanStdDev(results);
	int dataLen = results[0].DataLen;
	BenchmarkResult result(description, compressionLevel, blockSize, msd, dataLen);
	_benchmarkResults.push_back(result);
}

MeanStdDev BenchmarkStatistics::CalculateMeanStdDev(const vector<TimingResult>& results) {

	MeanStdDev msd;

	// calculate sums
	double numCompressionSecondsSum   = 0.0;
	double numDecompressionSecondsSum = 0.0;
	double compressionRatioSum        = 0.0;
	double compressionSpeedSum        = 0.0;
	double decompressionSpeedSum      = 0.0;

	for (auto it = results.begin(); it != results.end(); ++it) {
		numCompressionSecondsSum   += it->NumCompressionSeconds;
		numDecompressionSecondsSum += it->NumDecompressionSeconds;
		compressionRatioSum        += it->CompressionRatio;
		compressionSpeedSum        += it->CompressionBytesPerSecond;
		decompressionSpeedSum      += it->DecompressionBytesPerSecond;
	}

	// calculate means
	int numResults = (int)results.size();
	msd.NumCompressionSecondsMean   = numCompressionSecondsSum   / (double)numResults;
	msd.NumDecompressionSecondsMean = numDecompressionSecondsSum / (double)numResults;
	msd.CompressionRatioMean        = compressionRatioSum        / (double)numResults;
	msd.CompressionSpeedMean        = compressionSpeedSum        / (double)numResults;
	msd.DecompressionSpeedMean      = decompressionSpeedSum      / (double)numResults;

	// calculate standard deviations
	double compressionSpeedDiffSumSquare   = 0.0;
	double decompressionSpeedDiffSumSquare = 0.0;

	for (auto it = results.begin(); it != results.end(); ++it) {

		double compressionSpeedDiff   = it->CompressionBytesPerSecond - msd.CompressionSpeedMean;
		double decompressionSpeedDiff = it->DecompressionBytesPerSecond - msd.DecompressionSpeedMean;

		compressionSpeedDiffSumSquare   += compressionSpeedDiff * compressionSpeedDiff;
		decompressionSpeedDiffSumSquare += decompressionSpeedDiff * decompressionSpeedDiff;
	}

	double compressionSpeedVar   = compressionSpeedDiffSumSquare / (numResults - 1.0);
	double decompressionSpeedVar = decompressionSpeedDiffSumSquare / (numResults - 1.0);

	msd.CompressionSpeedStdDev   = sqrt(compressionSpeedVar);
	msd.DecompressionSpeedStdDev = sqrt(decompressionSpeedVar);

	return msd;
}
