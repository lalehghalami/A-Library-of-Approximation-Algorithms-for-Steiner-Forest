#ifndef PD_SF_hpp
#define PD_SF_hpp

#include <queue>

using namespace std;
void PrimalDualAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int>> *&adjList, vector<vector<int > > & pairedTerminals, int &solutionCost, int &initialSolution);

#endif /* PD_SF_hpp */
