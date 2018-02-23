#include "Tester.h"

int CompressQuickLz(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel)
{
	return QuickLzCompress(source, sourceLen, destination, destinationLen);
}

int DecompressQuickLz(char* source, int sourceLen, char* destination, int destinationLen)
{
	return QuickLzDecompress(source, destination, destinationLen);
}

int CompressZlib(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel)
{
	int comp_size = destinationLen;
	const int ret = bgzf_compress(destination, &comp_size, source, sourceLen, compressionLevel);

	if (ret == -1) {
		printf("ERROR: could not execute bgzf_compress: %d\n", ret);
		exit(1);
	}

	return comp_size;
}

int DecompressZlib(char* source, int sourceLen, char* destination, int destinationLen)
{
	return bgzf_decompress(destination, destinationLen, source, sourceLen);
}

int CompressZstd(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel)
{
	return (int)ZSTD_compress(destination, destinationLen, source, sourceLen, compressionLevel);
}

int DecompressZstd(char* source, int sourceLen, char* destination, int destinationLen)
{
	const int decompressed_size = (int)ZSTD_getDecompressedSize(source, sourceLen);

	if (decompressed_size > destinationLen)
	{
		printf("ERROR: The uncompressed block is too small (%d) for the uncompressed data (%d).\n", destinationLen, decompressed_size);
		exit(1);
	}

	return (int)ZSTD_decompress(destination, destinationLen, source, sourceLen);
}

int CompressSnappy(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel)
{
	size_t outputLen = destinationLen;
	const snappy_status status = snappy_compress(source, sourceLen, destination, &outputLen);

	if (status != SNAPPY_OK)
	{
		printf("ERROR: could not execute snappy_compress: %d, destination len: %d\n", status, destinationLen);
		exit(1);
	}

	return (int)outputLen;
}

int DecompressSnappy(char* source, int sourceLen, char* destination, int destinationLen)
{
	size_t outputLen = destinationLen;

	if (snappy_uncompress(source, sourceLen, destination, &outputLen) != SNAPPY_OK)
	{
		printf("ERROR: could not execute snappy_uncompress\n");
		exit(1);
	}

	return (int)outputLen;
}

int CompressLz4(char* source, int sourceLen, char* destination, int destinationLen, int compressionLevel)
{
	return LZ4_compress_default(source, destination, sourceLen, destinationLen);
}

int DecompressLz4(char* source, int sourceLen, char* destination, int destinationLen)
{
	return LZ4_decompress_safe(source, destination, sourceLen, destinationLen);
}

void BenchmarkAlgorithm(struct CompressionResults* results, const char* input_buffer, const int64_t input_buffer_size, 
	const char* output_buffer, int64_t output_buffer_size, const int block_size, const int compressionLevel)
{
	// ================
	// compression pass
	// ================

	printf("- evaluating %s (CL %d)... ", results->Description, compressionLevel);

	double startTime = get_time();

	int64_t numCompressedBytesTotal = 0;
	int64_t numBytesRemaining       = input_buffer_size;
	int64_t numOutputBytesRemaining = output_buffer_size;

	const int outputbufferSize = block_size * 2;

	const char* pIn  = input_buffer;
	const char* pOut = output_buffer;

	while (numBytesRemaining > 0)
	{
		if (numOutputBytesRemaining < 0)
		{
			printf("Negative output bytes available.\n");
			exit(1);
		}

		const int num_bytes_to_use = numBytesRemaining > block_size ? block_size : (int)numBytesRemaining;

		const int comp_size        = (*results->CompressFunc)(pIn, num_bytes_to_use, pOut, outputbufferSize, compressionLevel);

		numCompressedBytesTotal += comp_size;
		pOut                    += comp_size;
		pIn                     += num_bytes_to_use;
		numBytesRemaining       -= num_bytes_to_use;
		numOutputBytesRemaining -= num_bytes_to_use;
	}

	const double compressionSeconds = get_time() - startTime;

	// ==================
	// decompression pass
	// ==================

	//startTime = get_time();	

	//in  = fopen(compressedPath,   "rb");
	//out = fopen(uncompressedPath, "wb");

	//while (!feof(in))
	//{
	//	int comp_size;
	//	int numBytesRead = (int)fread((char*)&comp_size, 4, 1, in);
	//	if (numBytesRead == 0) break;

	//	numBytesRead = (int)fread(compressed, 1, comp_size, in);
	//	if (numBytesRead == 0) break;

	//	const int uncompressed_size = (*results->DecompressFunc)(compressed, comp_size, uncompressed, uncompressedLen);
	//	fwrite(uncompressed, 1, uncompressed_size, out);
	//}

	//fclose(out);
	//fclose(in);

	printf("finished.\n");

	//const double decompressionSeconds = get_time() - startTime;
	const double numMegabytes         = input_buffer_size / 1048576.0;
	const double compressionSpeed     = numMegabytes / compressionSeconds;
	//const double decompressionSpeed   = numMegabytes / decompressionSeconds;
	const double compressionRatio     = input_buffer_size / (double)numCompressedBytesTotal;

	printf("  Elapsed compression time:   %.3f s (%.1f MB/s)\n", compressionSeconds, compressionSpeed);
	//printf("  Elapsed decompression time: %.3f s (%.1f MB/s)\n", decompressionSeconds, decompressionSpeed);
	printf("  Compression ratio:          %.3fx\n\n", compressionRatio);

	//free(compressed);
	//free(uncompressed);

	//unlink(compressedPath);
}
