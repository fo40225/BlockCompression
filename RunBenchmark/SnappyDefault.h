#pragma once

#include "CompressionAlgorithm.h"
#include <sstream>

class Snappy : public CompressionAlgorithm {
public:
	Snappy(int blockSize);
	~Snappy();
	int Compress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const;
	int Decompress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const;
	int GetBlockSize(void) const { return _blockSize; }
	int GetCompressionLevel(void) const { return 1; }
	std::string GetDescription(void) const { return "Snappy"; }

private:
	int _blockSize;
};

