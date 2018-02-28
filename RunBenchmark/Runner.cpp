#include "Runner.h"
#include <iostream>

using namespace std;

Runner::Runner(vector<CompressionAlgorithm*> algorithms, int numReplicates)
	: _algorithms(algorithms)
	, _numReplicates(numReplicates)
{}

Runner::~Runner() {}

vector<TimingResult> Runner::EvaluateAlgorithm(CompressionData& data, const CompressionAlgorithm* pAlgorithm) {

	cout << pAlgorithm->GetDescription() << endl;
	vector<TimingResult> results(_numReplicates);

	for (int i = 0; i < _numReplicates; i++) {

		cout << "- replicate " << (i + 1) << ":" << endl;
		TimingResult result;
		data.Compress(pAlgorithm, result);
		data.Decompress(pAlgorithm, result);
		data.Verify(result);
		results.push_back(result);
		cout << endl;
	}

	cout << "Finished." << endl;
	exit(1);

	return results;
}

void Runner::Execute(CompressionData& data) {

	for (auto it = _algorithms.begin(); it != _algorithms.end(); ++it)
	{
		CompressionAlgorithm* pAlgorithm = *it;
		EvaluateAlgorithm(data, pAlgorithm);
	}
}
