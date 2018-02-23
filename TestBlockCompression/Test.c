#include <cstdio>
#include <cstdlib>
#include "CpuSupport.h"
#include "Tester.h"

#define VCF_BUFFER    3430000000
#define OUTPUT_BUFFER 2000000000

#define BLOCKSTREAM_SIZE 16777216

int64_t ReadFile(const char* input_path, char* input_buffer)
{
	printf("- loading file into memory... ");

	FILE* f = fopen(input_path, "rbe");
	
	fseek(f, 0, SEEK_END);
	const int64_t fsize = _ftelli64(f);
	fseek(f, 0, SEEK_SET);

	fread(input_buffer, 1, fsize, f);
	fclose(f);

	printf("finished.\n");
	return fsize;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("USAGE: %s <input_path>\n", argv[0]);
		exit(1);
	}

	if (HasAvx() == 1) printf("This processor has AVX support.\n");
	else printf("This processor DOES NOT HAVE AVX support.\n");
	printf("\n");

	const char* input_path    = argv[1];
	char* input_buffer        = malloc(VCF_BUFFER);
	const char* output_buffer = malloc(OUTPUT_BUFFER);

	const int64_t input_buffer_size = ReadFile(input_path, input_buffer);

	struct CompressionResults zlib_results = {
		"zlib",
		&CompressZlib,
		&DecompressZlib
	};

	struct CompressionResults quicklz_results = {
		"QuickLZ",
		&CompressQuickLz,
		&DecompressQuickLz
	};

	struct CompressionResults zstd_results = {
		"Zstd",
		&CompressZstd,
		&DecompressZstd
	};

	struct CompressionResults snappy_results = {
		"snappy",
		&CompressSnappy,
		&DecompressSnappy
	};

	struct CompressionResults lz4_results = {
		"LZ4",
		&CompressLz4,
		&DecompressLz4
	};

	//for (int cl = 1; cl <= 9; cl++)
	//{
	//	BenchmarkAlgorithm(&zlib_results, input_path, BGZF_MAX_BLOCK_SIZE, cl);
	//}

	//BenchmarkAlgorithm(&quicklz_results, input_path, BLOCKSTREAM_SIZE, 3);

	//for (int cl = 1; cl <= 22; cl++)
	//{
	//	BenchmarkAlgorithm(&zstd_results, input_path, BLOCKSTREAM_SIZE, cl);
	//}

	BenchmarkAlgorithm(&snappy_results, input_buffer, input_buffer_size, output_buffer, OUTPUT_BUFFER, BLOCKSTREAM_SIZE, 0);
	BenchmarkAlgorithm(&lz4_results, input_buffer, input_buffer_size, output_buffer, OUTPUT_BUFFER, BLOCKSTREAM_SIZE, 0);

	return 0;
}
