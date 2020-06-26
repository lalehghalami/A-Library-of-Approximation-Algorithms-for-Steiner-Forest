#ifndef TM_SF_hpp
#define TM_SF_hpp

#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <ctime>

#include "TM-Functions.h"
#include "SF-Functions.h"

using namespace std;

void treeMetricAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int>> *&adjList, vector<vector<int > > & pairedTerminals, int &solutionCost,int &diameter);

#endif /* TM_SF_hpp */
