#ifndef PD_SF_hpp
#define PD_SF_hpp

#include <queue>

using namespace std;
void PrimalDualAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<vector<int > > & adjMatrix, vector<vector<int > > & pairedTerminals, vector<vector<int > > & E ,int &cleanedSolution, int &initialSolution);

void PrimalDualAlgorithmNoPQ(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<vector<int > > & adjMatrix, vector<vector<int > > & pairedTerminals, vector<vector<int > > & E ,int &cleanedSolution, int &initialSolution);

#endif /* PD_SF_hpp */
