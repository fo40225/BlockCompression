#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ZlibNextGen.h"
#include "Zstandard.h"
#include "ZstandardDict.h"
#include "QuickLzLevel3.h"
#include "SnappyDefault.h"
#include "LZ4Default.h"
#include "Runner.h"
#include "bgzf.h"

using namespace std;

#define SA_BLOCK_SIZE 16777216

vector<CompressionAlgorithm*> GetCompressionAlgorithms(vector<char> dictBuffer) {

	vector<CompressionAlgorithm*> algorithms;

	for (int cl = 1; cl <= 9; cl++) {
		algorithms.push_back(new ZlibNextGen(cl, BGZF_MAX_BLOCK_SIZE));
	}

	for (int cl = 1; cl <= 22; cl++) {
		algorithms.push_back(new Zstandard(cl, SA_BLOCK_SIZE));
	}

	char* pDict  = dictBuffer.data();
	int dictSize = (int)dictBuffer.size();

	for (int cl = 1; cl <= 22; cl++) {
		algorithms.push_back(new ZstandardDict(cl, SA_BLOCK_SIZE, pDict, dictSize));
	}

	algorithms.push_back(new QuickLZ(SA_BLOCK_SIZE));
	algorithms.push_back(new Snappy(SA_BLOCK_SIZE));

	for (int cl = 1; cl <= 20; cl++) {
		algorithms.push_back(new LZ4(cl, SA_BLOCK_SIZE));
	}

	return algorithms;
}

vector<char> LoadDictionary(string dictPath) {

	ifstream ifs(dictPath.c_str(), ios::binary | ios::ate);
	ifstream::pos_type bufferSize = ifs.tellg();

	vector<char> buffer(bufferSize);

	ifs.seekg(0, ios::beg);
	ifs.read(&buffer[0], bufferSize);
	return buffer;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("USAGE: %s <input_path> <input_dict>\n", argv[0]);
		exit(1);
	}

	string inputPath = argv[1];
	string dictPath  = argv[2];

	CompressionData data(inputPath);
	data.Load();

	auto dictBuffer = LoadDictionary(dictPath);

	auto algorithms = GetCompressionAlgorithms(dictBuffer);
	const int numReplicates = 2;

	Runner runner(algorithms, numReplicates);
	runner.Execute(data);

	return 0;
}
