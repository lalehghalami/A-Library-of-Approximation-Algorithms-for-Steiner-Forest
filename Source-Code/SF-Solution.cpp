#include "SF-Solution.h"
using namespace std;

steinerForest::steinerForest(int V)
{
    this->V = V;
    adj = new vector<node>[V];
}

void steinerForest::addEdge(int v, int w, int wei)
{
    node vNode(v,wei);
    node WNode(w, wei);
    adj[v].push_back(WNode); // Add w to v’s list.
    adj[w].push_back(vNode); // Add v to w’s list.
}

bool steinerForest::BFS(int s,int t)
{
    int u;
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
    visited[i] = false;
    
    queue<int> myQueue;
    visited[s] = true;
    myQueue.push(s);
    
    while(!myQueue.empty())
    {
        u = myQueue.front();
        myQueue.pop();
        
        for (int i=0; i< adj[u].size(); i++)
        {
            if ((!visited[adj[u][i].index]) && (adj[u][i].needed))
            {
                visited[adj[u][i].index] = true;
                myQueue.push(adj[u][i].index);
                if (adj[u][i].index==t) return true;
            }
        }
    }
    return false;
}

void steinerForest::BFSCleanSolution(int s,int t, int &sum)
{
    // in this algorithm, it finds the path between each pair in the initial solution and zero out the path for the next pair
    sum=0;
    int u;
    bool *visited = new bool[V];
    int *pred = new int[V];
    int *We = new int[V];
    
    for(int i = 0; i < V; i++){
        visited[i] = false;
        pred[i]=-1;
        We[i]=0;
    }
    
    queue<int> myQueue;
    visited[s] = true;
    myQueue.push(s);
    
    while(!myQueue.empty())
    {
        u = myQueue.front();
        myQueue.pop();
        for (int i=0; i< adj[u].size(); i++)
        {
            if ((!visited[adj[u][i].index]))
            {
                visited[adj[u][i].index] = true;
                pred[adj[u][i].index]=u;
                We[adj[u][i].index]=adj[u][i].weight;
                myQueue.push(adj[u][i].index);
                if (adj[u][i].index==t) {
                    queue<int> empty;
                    swap(myQueue,empty);
                    break;
                }
            }
        }
    }
    
    int currentV=t;
    while (pred[currentV]!=-1) {
        sum+=We[currentV];
        for (int i=0; i< adj[currentV].size(); i++)
        {
            if (adj[currentV][i].index==pred[currentV]) {
                adj[currentV][i].weight=0;
            }
        }
        for (int i=0; i< adj[pred[currentV]].size(); i++)
        {
            if (adj[pred[currentV]][i].index==currentV) {
                adj[pred[currentV]][i].weight=0;
            }
        }
        currentV=pred[currentV];
    }
}
