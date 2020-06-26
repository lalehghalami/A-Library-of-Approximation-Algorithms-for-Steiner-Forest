#include <iostream>
#include <cstdint>
#include <algorithm>

#include "SF-Functions.h"
#include "TM-SF.hpp"
#include "TM-Functions.h"

using namespace std;

void treeMetricAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int>> *&adjList, vector<vector<int > > & pairedTerminals, int &solutionCost, int &diameter)

{
    cout<<"--------------------------------------------"<<endl;
    cout<<"Starting Tree Metric Algorithm: \n";
    vector<vector<int> > pathMatrix;
    vector<int> vertexList;
    
    for (int i=0; i<nVertex; i++)
        vertexList.push_back(i);
    
    // *************************************************************************//
    // Pick a random permutation pi of VertexList(V)
    vector<int> vertexListPer=vertexList;
    random_shuffle ( vertexListPer.begin(), vertexListPer.end());
    
    // *************************************************************************//
    // Set Delta to the smallets power of 2 greater than 2* max d_uv
    // for d_uv we will find the shortest path
    
    findPath(adjList,pathMatrix,nVertex); // find the shortest path between all vertices
    // *************************************************************************//
    
    int delta=-1000000; // check it
    for (int i=0; i<nVertex; i++) {
        for (int j=0; j<nVertex; j++) {
            if (delta< pathMatrix[i][j])
                delta=pathMatrix[i][j];
        }
    }
    diameter=delta;
    delta=pow2roundup(delta*2);
    
    // *************************************************************************//
    // Pick r_0 between 1/2 and 1 uniformly at random;
    // set r_i =r0*2^i for all i : 1<= i <= log(delta)
    srand (static_cast <unsigned> (time(0)));
    
    float LOW=0.5;
    float HI=1.0;
    float r0 = LOW+ static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LOW)));
    int logDelta=log2(delta);
    vector <float> rVector; // vector of r_0 to r_logDelta
    rVector.push_back(r0);
    for (int i=1; i<logDelta+1; i++)
        rVector.push_back(r0*(pow(2,i)));
    
    // *************************************************************************//
    // Building the tree
    
    Tree treeMetricObj;
    int index=0;
    treeMetricObj.insertRoot(index,vertexList,logDelta);
    treeMetricObj.buildTreeMetric(nVertex,pathMatrix,vertexListPer,rVector);
    //    treeMetricObj.showTree(); // uncomment to show the tree
    
    // *************************************************************************//
    // Convert Tree to T' with nVertex
    
    treeMetricObj.shrinkTree();
//    treeMetricObj.showTree(); // uncomment to show the tree

    // *************************************************************************//    
    set<pairs,CustomComparitor> pathSet;
    int sum=0;
    for (int i=0; i<pairedTerminals.size(); i++) {
        vector<int> s;
        s.push_back(pairedTerminals[i][0]);
        vector<int> t;
        t.push_back(pairedTerminals[i][1]);
        sum+=treeMetricObj.findPathCost(s,t,pathMatrix,i,pathSet);
    }
    set<pairs> :: iterator it; //iterator to manipulate set
    for (it = pathSet.begin(); it!=pathSet.end(); it++){
        pairs m = *it; // returns pair to m
        solutionCost+=pathMatrix[m.first][m.second];
    }
    cout<<"The last line of Tree Metric Algorithm \n";
    cout<<"--------------------------------------------"<<endl;
}
