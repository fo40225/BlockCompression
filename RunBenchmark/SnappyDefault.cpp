#include "SnappyDefault.h"
#include "snappy-c.h"

using namespace std;

Snappy::Snappy(int blockSize)
	: _blockSize(blockSize)
{}

Snappy::~Snappy() {}

int Snappy::Compress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {

	size_t numCompressedBytes = destinationLen;
	snappy_status status = snappy_compress(source, sourceLen, (char*)destination, &numCompressedBytes);

	if (status != SNAPPY_OK) {
		printf("ERROR: could not execute snappy_compress: %d\n", status);
		exit(1);
	}

	return (int)numCompressedBytes;
}

int Snappy::Decompress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {
	
	size_t numUncompressedBytes = destinationLen;
	snappy_status status = snappy_uncompress(source, sourceLen, (char*)destination, &numUncompressedBytes);

	if (status != SNAPPY_OK) {
		printf("ERROR: could not execute snappy_uncompress: %d\n", status);
		exit(1);
	}

	return (int)numUncompressedBytes;
}