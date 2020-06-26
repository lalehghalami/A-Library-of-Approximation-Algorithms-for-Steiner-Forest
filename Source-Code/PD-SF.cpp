#include "SF-Solution.h"
#include "SF-Functions.h"
#include "PD-SF.hpp"

#define __STDC_LIMIT_MACROS
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <algorithm>
#include <cstdint>
#include <limits>
#include <queue>

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

void PrimalDualAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<vector<int > > & adjMatrix, vector<vector<int > > & pairedTerminals, vector<vector<int > > & E ,int &cleanedSolution, int &initialSolution)
{
    struct timeval time_start,time_end;
    gettimeofday(&time_start, NULL);
    cout<<"--------------------------------------------"<<endl;
    cout<<"Starting Primal Dual Algorithm: \n";
    steinerForest solutionGraph(nVertex); // Create the solution graph
    cout<<"n: "<<nVertex<<endl;
    cout<<"m: "<<nEdges<<endl;
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
    for(int e=0; e<nEdges; e++)
    {
        int i=E[e][0];
        int j=E[e][1];
        int w=adjMatrix[i][j];
        
        if (MoatSets[i][1]==1 && MoatSets[j][1]==1)
        {
            edges myEdge;
            myEdge.edgeWeight=double(w)/2;
            if (i < j)
            {
                myEdge.edgeCoordinates=make_pair(i,j);
                pq.push(myEdge);
            }
        }
        else if (MoatSets[i][1]==1 || MoatSets[j][1]==1)
        {
            edges myEdge;
            myEdge.edgeWeight=double(w);
            if (i < j)
            {
                myEdge.edgeCoordinates=make_pair(i,j);
                pq.push(myEdge);
            }
        }
        else if (MoatSets[i][1]==0 && MoatSets[j][1]==0)
        {
            edges myEdge;
            myEdge.edgeWeight=100000000;
            if (i < j)
            {
                myEdge.edgeCoordinates=make_pair(i,j);
                pq.push(myEdge);
            }
        }
    }
    
   cout<<"Here \n";
    vector<vector<int>> solutionVector;
    int itr=0;
    while (flag==0 && pq.size()!=0)
    {
        cout<<"############ "<<itr++<<endl;

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
        cout<<"Update MoatSets labels \n";
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
               
                solutionGraph.addEdge(v1,v2, adjMatrix[v1][v2]);
                initialSolution=initialSolution+adjMatrix[v1][v2];
//                solutionVector.push_back(selectedEdges[i]);
            }
        }
        // ----------------------------------------------------------------------------------------
        // Immidiately after adding the edges to the solution, will check if all pairs are connected if so then break the while loop
        cout<<"Here 0\n";

        flag=0;
        
        for (int i=0; i<pairedTerminals.size(); i++)
        {
            cout<<"("<<pairedTerminals[i][0]<<" , "<<pairedTerminals[i][1]<<" )\n";
            if (MoatSets[pairedTerminals[i][0]][0]==MoatSets[pairedTerminals[i][1]][0])
                flag=1;
            else
            {   flag=0;
                break;
            }
        }
        if (flag == 1) break;
        cout<<"Here 2\n";

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
                weight=adjMatrix[row][col];
 
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
                weight=adjMatrix[row][col];
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
    
     cout<<"Out of while loop \n";
    // Computing the final solution
    for (int i=0; i<pairedTerminals.size(); i++)
    {
        int localSum=0;
        solutionGraph.BFSCleanSolution(pairedTerminals[i][0],pairedTerminals[i][1],localSum);
        cleanedSolution=cleanedSolution+localSum;
    }
    gettimeofday(&time_end, NULL);
    double durationAlg = (time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec);
    cout<<"The last line of Primal Dual Algorithm \n";
    cout<<"PD initial solution: "<<initialSolution<<endl;
    cout<<"PD final solution: "<<cleanedSolution<<endl;
    cout<< "Time: "<<durationAlg<<"\n";
    cout<<"--------------------------------------------"<<endl;
};

void PrimalDualAlgorithmNoPQ(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<vector<int > > & adjMatrix, vector<vector<int > > & pairedTerminals, vector<vector<int > > & E ,int &cleanedSolution, int &initialSolution)
{
    struct timeval time_start,time_end;
    gettimeofday(&time_start, NULL);
    initialSolution=0;
    cleanedSolution=0;
    cout<<"--------------------------------------------"<<endl;
    cout<<"Starting Primal Dual Algorithm Without using Priority Queues: \n";
    steinerForest solutionGraph(nVertex); // Create the solution graph
    vector<vector<int>> solutionVector;
    
    // Initialization:
    vector<int> C(nVertex,0);
    vector<double> g(nVertex,0);
    vector<int> A(nVertex,0);
    for (int i=0; i<nVertex; i++) {
        C[i]=i;
        int *p;
        p = std::find (terminals, terminals+nTerminals, i);
        if ( p != terminals +nTerminals )
            A[i]=1;
    }
    int flag=0; // Flag =1 means all terminal pairs are connected
    
    
//    int itr=0;
    while (flag==0)
    {
//        cout<<"############ "<<itr++<<endl;
        double minKey=10000000; //????
        vector<vector<int > > selectedEdges;

        for(int e=0; e<E.size(); e++)
        {
            int i=E[e][0];
            int j=E[e][1];
            int w=adjMatrix[i][j];
            
            if (C[i]==C[j] || (A[i]==0 && A[j]==0))
                continue;
            
            double tempW=0;
            
            if (A[i]==1 && A[j]==1)
                tempW=double((w-g[i]-g[j])/2);
            else if (A[i]==1 || A[j]==1)
                tempW=double(w-g[i]-g[j]);
            
            if (tempW < minKey) {
                minKey=tempW;
                selectedEdges.clear();
                vector<int> tempV;
                tempV.push_back(i);
                tempV.push_back(j);
                selectedEdges.push_back(tempV);
            }else if(tempW==minKey)
            {
                vector<int> tempV;
                tempV.push_back(i);
                tempV.push_back(j);
                selectedEdges.push_back(tempV);
            }
        }

        // Update growth
        for (int i=0; i<nVertex; i++)
            if (A[i]==1)
                g[i]=double(g[i]+minKey);
        
        // Update MoatSets labels
        int minLabel;
        for (int e=0; e<selectedEdges.size(); e++) {
            int i=selectedEdges[e][0];
            int j=selectedEdges[e][1];
            A[i]=A[j]=1;
            int lable_i=C[i];
            int label_j=C[j];
            if (lable_i != label_j)
            {
                minLabel=min(lable_i,label_j);
                for (int v=0; v<nVertex; v++)
                {
                    if (C[v]==lable_i || C[v]==label_j)
                    {
                        C[v]=minLabel;
                    }
                }
                solutionGraph.addEdge(i,j, adjMatrix[i][j]);
                solutionVector.push_back(selectedEdges[e]);
                initialSolution=initialSolution+adjMatrix[i][j];
            }
        }

        // ----------------------------------------------------------------------------------------
        // Immidiately after adding the edges to the solution, will check if all pairs are connected if so then break the while loop
        flag=0;
        
        for (int i=0; i<pairedTerminals.size(); i++)
        {
            if (C[pairedTerminals[i][0]]==C[pairedTerminals[i][1]])
                flag=1;
            else
            {   flag=0;
                break;
            }
        }
        if (flag == 1) break;
        
        // ------------------------------------------
        // Updating the list of edges
        vector<vector<int> > Etemp;
        for(int e=0; e<E.size(); e++)
        {
            int i=E[e][0];
            int j=E[e][1];
            if (C[i]!=C[j])
            {
                Etemp.push_back(E[e]);
            }
        }

        E.clear();
        E=Etemp;
        Etemp.clear();
        selectedEdges.clear();
    }// end of the while loop

    // Computing the final solution
    for (int i=0; i<pairedTerminals.size(); i++)
    {
        int localSum=0;
        solutionGraph.BFSCleanSolution(pairedTerminals[i][0],pairedTerminals[i][1],localSum);
        cleanedSolution=cleanedSolution+localSum;
    }
    
    gettimeofday(&time_end, NULL);
    double durationAlg = (time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec);
    
    cout<<"The last line of Primal Dual Algorithm \n";
    cout<<"PD-NoPQ initial solution: "<<initialSolution<<endl;
    cout<<"PD-NoPQ final solution: "<<cleanedSolution<<endl;
    cout<< "Time: "<<durationAlg<<"\n";
    cout<<"--------------------------------------------"<<endl;
}
