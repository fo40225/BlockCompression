#include "QuickLzLevel3.h"
#include "quicklz.h"

using namespace std;

QuickLZ::QuickLZ(int blockSize)
	: _blockSize(blockSize)
{}

QuickLZ::~QuickLZ() {}

int QuickLZ::Compress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {

	const int numCompressedBytes = QuickLzCompress((char*)source, sourceLen, (char*)destination, destinationLen);

	if (numCompressedBytes < 0) {
		printf("ERROR: could not execute QuickLzCompress: %d\n", numCompressedBytes);
		exit(1);
	}

	return numCompressedBytes;
}

int QuickLZ::Decompress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {
	return QuickLzDecompress((char*)source, (char*)destination, destinationLen);
}
