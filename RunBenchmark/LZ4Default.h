#pragma once

#include "CompressionAlgorithm.h"
#include <sstream>

class LZ4 : public CompressionAlgorithm {
public:
	LZ4(int compressionLevel, int blockSize);
	~LZ4();
	int Compress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const;
	int Decompress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const;
	int GetBlockSize(void) const { return _blockSize; }
	int GetCompressionLevel(void) const { return _compressionLevel; }
	std::string GetDescription(void) const { return "LZ4"; }

private:
	int _blockSize;
	int _compressionLevel;
};
