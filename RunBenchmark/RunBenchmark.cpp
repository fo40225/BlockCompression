#include <iostream>
#include <string>
#include <vector>
#include "CpuSupport.h"
#include "ZlibNextGen.h"
#include "Zstandard.h"
#include "QuickLzLevel3.h"
#include "SnappyDefault.h"
#include "LZ4Default.h"
#include "Runner.h"
#include "bgzf.h"

using namespace std;

void ShowAvxStatus(void) {
	if (HasAvx() == 1) cout << "This processor has AVX support." << endl;
	else cout << "This processor DOES NOT HAVE AVX support." << endl;
	cout << endl;
}

#define SA_BLOCK_SIZE 16777216

vector<CompressionAlgorithm*> GetCompressionAlgorithms() {

	vector<CompressionAlgorithm*> algorithms;

	for (int cl = 1; cl <= 9; cl++) {
		algorithms.push_back(new ZlibNextGen(cl, BGZF_MAX_BLOCK_SIZE));
	}

	for (int cl = 1; cl <= 22; cl++) {
		algorithms.push_back(new Zstandard(cl, SA_BLOCK_SIZE));
	}

	algorithms.push_back(new QuickLZ(SA_BLOCK_SIZE));
	algorithms.push_back(new Snappy(SA_BLOCK_SIZE));

	for (int cl = 1; cl <= 20; cl++) {
		algorithms.push_back(new LZ4(cl, SA_BLOCK_SIZE));
	}

	return algorithms;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("USAGE: %s <input_path>\n", argv[0]);
		exit(1);
	}

	ShowAvxStatus();

	string inputPath = argv[1];
	CompressionData data(inputPath);
	data.Load();

	auto algorithms = GetCompressionAlgorithms();
	const int numReplicates = 5;

	Runner runner(algorithms, numReplicates);
	runner.Execute(data);

	return 0;
}
