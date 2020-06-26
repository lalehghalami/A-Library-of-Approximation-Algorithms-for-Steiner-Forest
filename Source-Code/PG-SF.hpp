#ifndef PG_SF_hpp
#define PG_SF_hpp

#include <fstream>
#include <vector>

using namespace std;

void greedyAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int> > *&adjList, vector<vector<int > > & pairedTerminals, int &cleanedSolution,int &initialSolution);

#endif /* PG_SF_hpp */
