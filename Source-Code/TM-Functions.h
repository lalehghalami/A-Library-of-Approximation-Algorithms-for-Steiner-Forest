#ifndef TM_Functions_h
#define TM_Functions_h


#include <iostream>
#include <set>
#include <stack>
#include <queue>

using namespace std;

typedef pair<int, int> pairs;

class CustomComparitor
{
public:
    
    bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const{
        
        if ((lhs.first == rhs.first) && (lhs.second == rhs.second)) return true;  // ADD THIS LINE
        else if ((lhs.first == rhs.second) && (lhs.second == rhs.first)) return true;
        else return ((lhs.first > rhs.first) || (lhs.first < rhs.first));
        //else return false;
    }
};

class Tree
{
    
private:
    
    class TreeNodes
    {
    public:
        
        TreeNodes( const int index, vector <int> set, TreeNodes *parentPtr, int Lv)
        {
            nodeIndex=index;
            nodeSet=set;
            firstChild=0;
            nextSibling=0;
            parent=parentPtr;
            level=Lv;
            terminalPair=-1;
        }
        
        vector <int> nodeSet;
        int nodeIndex;
        int level;
        TreeNodes *firstChild;
        TreeNodes *nextSibling;
        TreeNodes *parent;
        int terminalPair;
        
    };
    TreeNodes *root;
    
public:
    
    Tree();
    void insertRoot(int index, vector<int> set, int Lv);
    void insert(TreeNodes *p, int index, vector<int> set,int Lv);
    void buildTreeMetric(int nVertex,vector<vector<int> > pathMatrix,vector<int> vertexListPer,vector <float> rVector );
    void showTree();
    void shrinkTree();
    int findPathCost(vector<int> s, vector<int> t,vector<vector<int> > pathMatrix, int terminalPairIndex, set<pair<int,int>,CustomComparitor> & pathSet);
};

#endif /* TM_Functions_h */






