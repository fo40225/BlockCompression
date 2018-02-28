#include "CompressionData.h"
#include <fstream>
#include <iostream>
#include "Benchmark.h"
#include "MemoryUtilities.h"

using namespace std;

#define GIGABYTE 1073741824

CompressionData::CompressionData(const std::string& inputPath)
	: _inputPath(inputPath)
{}

CompressionData::~CompressionData() {}

void CompressionData::Load(void) {

	cout << "Loading " << _inputPath << "... " << flush;

	ifstream in(_inputPath.c_str(), ios::binary | ios::ate);
	ifstream::pos_type position = in.tellg();

	_dataLen = position > GIGABYTE ? GIGABYTE : (int)position;

	_data.resize(_dataLen);
	in.seekg(0, ios::beg);
	in.read(&_data[0], _dataLen);

	_compressedData.resize(2 * _dataLen);
	_decompressedData.resize(2 * _dataLen);

	cout << "read " << MemoryUtilities::ToHumanReadable(_dataLen) << endl << endl;
}

void CompressionData::Compress(const CompressionAlgorithm* pAlgorithm, TimingResult& result) {

	int numBytesRemaining       = _dataLen;
	int numOutputBytesRemaining = (int)_compressedData.size();
	int numCompressedBytes      = 0;

	const char* pIn     = _data.data();
	const char* pOut    = _compressedData.data();
	const int blockSize = pAlgorithm->GetBlockSize();

	Benchmark benchmark;

	while (numBytesRemaining > 0)
	{
		if (numOutputBytesRemaining < 0)
		{
			cout << "Negative output bytes available." << endl;
			exit(1);
		}

		const int numBytesToCompress = numBytesRemaining > blockSize ? blockSize : (int)numBytesRemaining;
		const int compressedLen      = pAlgorithm->Compress(pIn, numBytesToCompress, pOut, numBytesRemaining);

		pIn                += numBytesToCompress;
		pOut               += compressedLen;
		numCompressedBytes += compressedLen;

		numBytesRemaining       -= numBytesToCompress;
		numOutputBytesRemaining -= compressedLen;
	}
	
	double numSeconds = benchmark.GetElapsedSeconds();
	double speed = Benchmark::GetSpeed(_dataLen, numSeconds);
	cout << "- compression: " << Benchmark::ConvertSpeed(speed) << " (" << MemoryUtilities::ToHumanReadable(numCompressedBytes) << ")" << endl;

	result.CompressionBytesPerSecond = speed;
	result.CompressionRatio          = (double)_dataLen / (double)numCompressedBytes;
}

void CompressionData::Decompress(const CompressionAlgorithm* pAlgorithm, TimingResult& result) {

	//int numBytesRemaining       = (int)_compressedData.size();
	//int numOutputBytesRemaining = (int)_decompressedData.size();
	//int numDecompressedBytes    = 0;

	//const char* pIn  = _compressedData.data();
	//const char* pOut = _decompressedData.data();

	//Benchmark benchmark;

	//while (numBytesRemaining > 0)
	//{
	//	if (numOutputBytesRemaining < 0)
	//	{
	//		cout << "Negative output bytes available." << endl;
	//		exit(1);
	//	}

	//	const int numBytesToCompress = numBytesRemaining > blockSize ? blockSize : (int)numBytesRemaining;
	//	const int compressedLen = pAlgorithm->Compress(pIn, numBytesToCompress, pOut, numBytesRemaining);

	//	pIn += numBytesToCompress;
	//	pOut += compressedLen;
	//	numCompressedBytes += compressedLen;

	//	numBytesRemaining -= numBytesToCompress;
	//	numOutputBytesRemaining -= compressedLen;
	//}


}

void CompressionData::Verify(TimingResult& result) {

}
