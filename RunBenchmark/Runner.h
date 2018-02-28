#pragma once

#include <vector>
#include "CompressionAlgorithm.h"
#include "CompressionData.h"
#include "TimingResult.h"

class Runner {
public:
	Runner(std::vector<CompressionAlgorithm*> algorithms, int numReplicates);
	~Runner();
	void Execute(CompressionData& data);
	std::vector<TimingResult> EvaluateAlgorithm(CompressionData& data, const CompressionAlgorithm* pAlgorithm);

private:
	std::vector<CompressionAlgorithm*> _algorithms;
	int _numReplicates;
};

