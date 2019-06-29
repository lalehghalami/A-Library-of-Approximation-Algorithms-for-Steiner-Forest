#ifndef SF_Solution_h
#define SF_Solution_h
#include <iostream>
#include <queue>

using namespace std;

class steinerForest
{
    
    public:
    steinerForest(int V);
    void addEdge(int v, int w,int wei);
    bool BFS(int s,int t);
    void BFSCleanSolution(int s,int t, int &sum);
    
    class node
    {
        public:
        node(int i, int w)
        {
            index=i;
            needed=true;
            weight=w;
        }
        int index;
        bool needed;
        int weight;
        
    };
    int V;    // No. of vertices, initialy we add all vertices
    vector<node> *adj; // Pointer to an array containing adjacency lists
};

#endif /* SF_Solution_h */
