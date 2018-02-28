#include <iostream>
#include <string>
#include <vector>
#include "CpuSupport.h"
#include "ZlibNextGen.h"
#include "Runner.h"
#include "bgzf.h"

using namespace std;

void ShowAvxStatus(void) {
	if (HasAvx() == 1) cout << "This processor has AVX support." << endl;
	else cout << "This processor DOES NOT HAVE AVX support." << endl;
	cout << endl;
}

vector<CompressionAlgorithm*> GetCompressionAlgorithms() {

	vector<CompressionAlgorithm*> algorithms;

	for (int cl = 1; cl <= 9; cl++) {
		algorithms.push_back(new ZlibNextGen(cl, BGZF_MAX_BLOCK_SIZE));
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
	const int numReplicates = 3;

	Runner runner(algorithms, numReplicates);
	runner.Execute(data);

	return 0;
}
