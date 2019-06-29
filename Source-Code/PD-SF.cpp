#include "SF-Solution.h"
#include "SF-Functions.h"
#include "PD-SF.hpp"

using namespace std;

class edges
{
public:
    double edgeWeight;
    pair<int,int> edgeCoordinates;
};

bool operator< (const edges& lhs, const edges& rhs)
{
    return lhs.edgeWeight < rhs.edgeWeight;
}

bool operator> (const edges& lhs, const edges& rhs)
{
    return lhs.edgeWeight > rhs.edgeWeight;
}

bool operator== (const edges& lhs, const edges& rhs)
{
    return (lhs.edgeCoordinates.first == rhs.edgeCoordinates.first)||(lhs.edgeCoordinates.second == rhs.edgeCoordinates.first);
}

void PrimalDualAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int>> *&adjList, vector<vector<int > > & pairedTerminals, int &cleanedSolution, int &initialSolution)
{
    cout<<"--------------------------------------------"<<endl;
    cout<<"Starting Primal Dual Algorithm: \n";
    steinerForest solutionGraph(nVertex); // Create the solution graph
    
    // Initialize MoatSets:
    // MoatSets[i][0] keeps the moat label of vertex i, MoatSets[i][1] shows if the vertex is in an active moat, MoatSets[i][2] shows the growth rate for the vertex
    vector<vector < double > > MoatSets;
    vector<double> moatRow(3, 0);
    for (int i=0; i<nVertex; i++)
        MoatSets.push_back(moatRow);
    
    for (int i=0; i<nVertex; i++) {
        MoatSets[i][0]=i;
        MoatSets[i][1]=0;
        MoatSets[i][2]=0;
        
        int *p;
        p = std::find (terminals, terminals+nTerminals, i);
        if ( p != terminals +nTerminals )
            MoatSets[i][1]=1;
    }
    int flag=0; // Flag =1 means all terminal pairs are connected
    
    priority_queue <edges, vector<edges>, greater<edges> > pq;
    for(int i = 0; i < nVertex; i++)
    {
        for(int j = 0; j < adjList[i].size(); j++)
        {
            if (MoatSets[i][1]==1 && MoatSets[adjList[i][j].first][1]==1)
            {
                edges myEdge;
                myEdge.edgeWeight=double(adjList[i][j].second)/2;
                int cord_1= i;
                int cord_2= adjList[i][j].first;
                if (i < adjList[i][j].first)
                {
                    myEdge.edgeCoordinates=make_pair(cord_1,cord_2);
                    pq.push(myEdge);
                }
            }
            else if (MoatSets[i][1]==1 || MoatSets[adjList[i][j].first][1]==1)
            {
                edges myEdge;
                myEdge.edgeWeight=double(adjList[i][j].second);
                int cord_1= i;
                int cord_2= adjList[i][j].first;
                if (i < adjList[i][j].first)
                {
                    myEdge.edgeCoordinates=make_pair(cord_1,cord_2);
                    pq.push(myEdge);
                }
            }
            else if (MoatSets[i][1]==0 && MoatSets[adjList[i][j].first][1]==0)
            {
                edges myEdge;
                myEdge.edgeWeight=INT_MAX;
                int cord_1= i;
                int cord_2= adjList[i][j].first;
                if (i < adjList[i][j].first)
                {
                    myEdge.edgeCoordinates=make_pair(cord_1,cord_2);
                    pq.push(myEdge);
                }
            }
        }
    }
    
    vector<vector<int>> solutionVector;
    while (flag==0)
    {
        vector<edges> selectedEdges;
        edges minEdge=pq.top();
        selectedEdges.push_back(minEdge);
        double minKey=minEdge.edgeWeight;
        double growth=double(minKey);
        for (int j=0; j<nVertex; j++)
        {
            if (MoatSets[j][1]==1) // Update growth
                MoatSets[j][2]=double(MoatSets[j][2]+growth);
        }
        pq.pop();
        // All edges that has the minimum weight will be added to the selectedEdges
        if(pq.size()!=0){
            int pqFlag=1;
            while (pqFlag) {
                if (pq.top().edgeWeight==minKey)
                {
                    edges minEdgeNext=pq.top();
                    selectedEdges.push_back(minEdgeNext);
                    pq.pop();
                    if(pq.size()==0)pqFlag=0;
                }else
                    pqFlag=0;
            }
        }
        
        // Update MoatSets labels
        int minLabel;
        for (int i=0; i<selectedEdges.size(); i++) {
            int v1=selectedEdges[i].edgeCoordinates.first;
            int v2=selectedEdges[i].edgeCoordinates.second;
            MoatSets[v1][1]=MoatSets[v2][1]=1; // Update activity
            int label1=MoatSets[v1][0];
            int label2=MoatSets[v2][0];
            if (label1!=label2) //only those minimum edges that don't cause loop in the forest will be added to the solution
            {
                minLabel=min(label1,label2);
                for (int j=0; j<nVertex; j++) // Update MoatSets labels
                {
                    if(MoatSets[j][0]==label1 || MoatSets[j][0]==label2)
                        MoatSets[j][0]=minLabel;
                }
                int localW=0;
                for (int k=0; k<adjList[selectedEdges[i].edgeCoordinates.first].size(); k++) {
                    if (adjList[selectedEdges[i].edgeCoordinates.first][k].first==selectedEdges[i].edgeCoordinates.second) {
                        localW=adjList[selectedEdges[i].edgeCoordinates.first][k].second;
                    }
                }
                solutionGraph.addEdge(selectedEdges[i].edgeCoordinates.first,selectedEdges[i].edgeCoordinates.second, localW);
            }
        }
        
        // ----------------------------------------------------------------------------------------
        // Immidiately after adding the edges to the solution, will check if all pairs are connected if so then break the while loop
        flag=0;
        
        for (int i=0; i<pairedTerminals.size(); i++)
        {
            if (MoatSets[pairedTerminals[i][0]][0]==MoatSets[pairedTerminals[i][1]][0])
                flag=1;
            else
            {   flag=0;
                break;
            }
        }
        if (flag == 1) break;
        
        // ------------------------------------------
        // Updating the Priority Queue
        
        priority_queue <edges, vector<edges>, greater<edges> > tempPQ;
        while (!pq.empty())
        {
            edges tempEdge=pq.top();
            int row=tempEdge.edgeCoordinates.first;
            int col=tempEdge.edgeCoordinates.second;
            double weight=0;
            
            if(MoatSets[row][0]==MoatSets[col][0]) // both endpoints are in the current/same moats then we just pop out the edge, we already picket the minimum between two components and added to the solution rest should be grrater than it
                pq.pop();
            else if(MoatSets[col][1]==1 && MoatSets[row][1]==1) // both endpoints are in the active moats
            {
                for(int j = 0; j < adjList[row].size(); j++)
                    if (adjList[row][j].first==col) {
                        weight=adjList[row][j].second;
                    }
                if (weight!=0)
                {
                    double updatedWeigh=double(weight-MoatSets[row][2]-MoatSets[col][2]);
                    updatedWeigh=double(updatedWeigh)/2;
                    tempEdge.edgeWeight=updatedWeigh;
                    tempPQ.push(tempEdge);
                    pq.pop();
                }
            }
            else if(MoatSets[col][1]==0 && MoatSets[row][1]==0)
            {
                tempPQ.push(tempEdge);
                pq.pop();
            }
            else if(MoatSets[col][1]==0 || MoatSets[row][1]==0)
            {
                
                for(int j = 0; j < adjList[row].size(); j++)
                    if (adjList[row][j].first==col) {
                        weight=adjList[row][j].second;
                    }
                if (weight!=0)
                {
                    double updatedWeigh=double(weight-MoatSets[row][2]-MoatSets[col][2]);
                    tempEdge.edgeWeight=updatedWeigh;
                    tempPQ.push(tempEdge);
                    pq.pop();
                }
            }
        }
        pq=tempPQ;
        
        while (!tempPQ.empty()) {
            tempPQ.pop();}
        
        selectedEdges.clear();
    }// end of the while loop
    
    
    // Computing the initial solution, without cleaning, for verifiction purpose
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
                    weight = (*it).second;
                    initialSolution+=weight;
                }
            }
        }
    }
    
    // Computing the final solution
    for (int i=0; i<pairedTerminals.size(); i++)
    {
        int localSum=0;
        solutionGraph.BFSCleanSolution(pairedTerminals[i][0],pairedTerminals[i][1],localSum);
        cleanedSolution=cleanedSolution+localSum;
    }
    cout<<"The last line of Primal Dual Algorithm \n";
    cout<<"--------------------------------------------"<<endl;
}
