#ifndef GL_SF_hpp
#define GL_SF_hpp

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class terminal
{
public:
    int myIndex;
    int myMateIndex;
    bool active;
    terminal(int node,int mateNode, bool status)
    {
        myIndex=node;
        myMateIndex=mateNode;
        active=status;
    }
    int getIndex() const
    {
        return myIndex;
    }
    int getMate() const
    {
        return myMateIndex;
    }
    void displayInfo()
    {
        cout << myIndex << " :: " << myMateIndex << endl;
    }
    
    bool operator ==(const terminal & obj) const
    {
        if (myIndex == obj.getIndex())
            return true;
        else
            return false;
    }
    
    void updateState()
    {
        active=false;
    }
    
};


namespace std
{
    template<>
    struct hash<terminal>
    {
        size_t operator()(const terminal & obj) const
        {
            return hash<int>()(obj.getIndex());
        }
    };
}


class supernode
{
public:
    
    unordered_map <int,terminal> supernodeList;
    
    bool active;
};


void gluttonousAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int > > *&adjList, vector<vector<int > > & pairedTerminals, int &cleanedSolution,int &initialSolution);

#endif /* Gluttonous_Algorithm_hpp */
