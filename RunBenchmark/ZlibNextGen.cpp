#include "ZlibNextGen.h"
#include "bgzf_decompress.h"
#include "bgzf.h"

using namespace std;

ZlibNextGen::ZlibNextGen(int compressionLevel, int blockSize)
	: _compressionLevel(compressionLevel)
	, _blockSize(blockSize)
{}

ZlibNextGen::~ZlibNextGen() {}

int ZlibNextGen::Compress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {
	int comp_size = destinationLen;
	const int ret = bgzf_compress((char*)destination, &comp_size, source, sourceLen, _compressionLevel);

	if (ret == -1) {
		printf("ERROR: could not execute bgzf_compress: %d\n", ret);
		exit(1);
	}

	return comp_size;
}

int ZlibNextGen::Decompress(const char* source, const int sourceLen, const char* destination, const int destinationLen) const {
	return bgzf_decompress((char*)destination, destinationLen, (char*)source, sourceLen);
}
