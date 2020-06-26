#include "PG-SF.hpp"
#include "SF-Solution.h"
#include "SF-Functions.h"
#include <cstdint>

using namespace std;

void greedyAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int>> *&adjList, vector<vector<int > > & pairedTerminals, int &cleanedSolution,int &initialSolution)
{
    cout<<"--------------------------------------------"<<endl;
    cout<<"Starting Paird Greedy Algorithm: \n";
    vector<vector<int> > updatedPairedTerminals;
    vector<pair<int,int>> *adjListCopy;
    updatedPairedTerminals=pairedTerminals;
    adjListCopy=adjList;
    
    steinerForest solutionGraph(nVertex);
    int* sitesDist=new int[nTerminals/2];
    int flag=0;
    
    while (flag==0)
    {
        int holdIndex=-1;
        int selectedSite=100000000;
        vector<vector< int > > selectedEdges;
        for (int i=0; i<updatedPairedTerminals.size(); i++)
        {
            vector<vector< int > > path;
            sitesDist[i]=dijkstra(updatedPairedTerminals[i][0],updatedPairedTerminals[i][1],nVertex, adjListCopy, path);
            if (sitesDist[i]<selectedSite)
            {
                selectedSite=sitesDist[i];
                selectedEdges.clear();
                selectedEdges=path;
                holdIndex=i;
            }
        }
        
        //--------------------------------------------------------------------------------------------
        // Zero out this path, i.e. make its length as 0 and include the path in the solution
        for (int i=0; i<selectedEdges.size(); i++) {
            int localW=0;
            for (int j=0; j<adjList[selectedEdges[i][0]].size(); j++) {
                if (adjList[selectedEdges[i][0]][j].first==selectedEdges[i][1]) {
                    localW=adjList[selectedEdges[i][0]][j].second;
                }
            }
            
            solutionGraph.addEdge(selectedEdges[i][0],selectedEdges[i][1],localW);
            vector< pair<int, int> >::iterator j;
            for (j = adjListCopy[selectedEdges[i][0]].begin(); j != adjListCopy[selectedEdges[i][0]].end(); ++j)
            {
                int weight;
                int v = (*j).first;
                if (v==selectedEdges[i][1]) {
                    weight = (*j).second;
                    (*j).second=0;
                }
            }
            for (j = adjListCopy[selectedEdges[i][1]].begin(); j != adjListCopy[selectedEdges[i][1]].end(); ++j)
            {
                int weight;
                int v = (*j).first;
                if (v==selectedEdges[i][0]) {
                    weight = (*j).second;
                    (*j).second=0;
                }
            }
        }
        
        updatedPairedTerminals.erase(updatedPairedTerminals.begin() + holdIndex); // remove the connected sites from the sites set
        
        flag=0;
        for (int i=0; i<pairedTerminals.size(); i++)
        {
            if(solutionGraph.BFS(pairedTerminals[i][0],pairedTerminals[i][1]))
                flag=1;
            else
            {
                flag=0;
                break;
            }
        }
    } // end of the while loop
    
    //---------------------------------------------------------------------------------------------------------------------
    for (int i=0; i<nVertex; i++)
    {
        for(int j=0; j< solutionGraph.adj[i].size(); j++)
        {
            vector< pair<int, int> >::iterator it;
            for (it = adjList[i].begin(); it != adjList[i].end(); ++it)
            {
                int weight;
                int v = (*it).first;
                if (v==solutionGraph.adj[i][j].index) {
                    weight = solutionGraph.adj[i][j].weight;
                    initialSolution=initialSolution+weight;
                }
            }
        }
    }
    
    for (int i=0; i<pairedTerminals.size(); i++)
    {
        int sumLocal=0;
        solutionGraph.BFSCleanSolution(pairedTerminals[i][0],pairedTerminals[i][1],sumLocal);
        cleanedSolution=cleanedSolution+sumLocal;
    }
    cout<<"The last line of Paird Greedy Algorithm \n";
    cout<<"--------------------------------------------"<<endl;
    delete [] sitesDist;
}
