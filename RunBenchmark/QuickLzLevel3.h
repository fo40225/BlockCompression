#pragma once

#include "CompressionAlgorithm.h"
#include <sstream>

class QuickLZ : public CompressionAlgorithm {
public:
	QuickLZ(int blockSize);
	~QuickLZ();
	int Compress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const;
	int Decompress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const;
	int GetBlockSize(void) const { return _blockSize; }
	int GetCompressionLevel(void) const { return 3; }
	std::string GetDescription(void) const { return "QuickLZ"; }

private:
	int _blockSize;
};

