#include "LZ4Default.h"
#include "lz4.h"

using namespace std;

LZ4::LZ4(int compressionLevel, int blockSize)
	: _compressionLevel(compressionLevel)
	, _blockSize(blockSize)
{}

LZ4::~LZ4() {}

int LZ4::Compress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {

	const int numCompressedBytes = LZ4_compress_fast(source, (char*)destination, sourceLen, destinationLen, _compressionLevel);

	if (numCompressedBytes < 0) {
		printf("ERROR: could not execute LZ4_compress_default: %d\n", numCompressedBytes);
		exit(1);
	}

	return numCompressedBytes;
}

int LZ4::Decompress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {
	return LZ4_decompress_safe(source, (char*)destination, sourceLen, destinationLen);
}
