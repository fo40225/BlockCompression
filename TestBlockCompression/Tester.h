#pragma once

#include <stdio.h>
#include "bgzf.h"
#include "BlockGZipUtils.h"
#include "quicklz.h"
#include "zstd.h"
#include "Benchmark.h"
#include "snappy-c.h"
#include "lz4.h"

#define PATH_LEN 1024

#ifdef _MSC_VER
#define unlink _unlink
#endif

struct CompressionResults
{
	const char* Description;
	int (*CompressFunc)(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel);
	int (*DecompressFunc)(char* source, int sourceLen, char* destination, int destinationLen);
};

void BenchmarkAlgorithm(struct CompressionResults* results, const char* input_buffer, int64_t input_buffer_size, 
	const char* output_buffer, int64_t output_buffer_size, int block_size, int compressionLevel);

int CompressZlib(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel);
int DecompressZlib(char* source, int sourceLen, char* destination, int destinationLen);
int CompressQuickLz(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel);
int DecompressQuickLz(char* source, int sourceLen, char* destination, int destinationLen);
int CompressZstd(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel);
int DecompressZstd(char* source, int sourceLen, char* destination, int destinationLen);
int CompressSnappy(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel);
int DecompressSnappy(char* source, int sourceLen, char* destination, int destinationLen);
int CompressLz4(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel);
int DecompressLz4(char* source, int sourceLen, char* destination, int destinationLen);
