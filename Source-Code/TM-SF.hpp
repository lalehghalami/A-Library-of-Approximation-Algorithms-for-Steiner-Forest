#ifndef TM_SF_hpp
#define TM_SF_hpp


#include <unordered_map>
#include <ctime>

#include "TM-Functions.h"
#include "SF-Functions.h"

using namespace std;

void treeMetricAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int>> *&adjList, vector<vector<int > > & pairedTerminals, int &solutionCost);

#endif /* TM_SF_hpp */
