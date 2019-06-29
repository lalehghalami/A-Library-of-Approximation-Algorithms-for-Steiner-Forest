#include "SF-Solution.h"
#include "SF-Functions.h"
#include "GL-SF.hpp"

using namespace std;

void gluttonousAlgorithm(int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int>> *&adjList, vector<vector<int > > & pairedTerminals, int &cleanedSolution,int &initialSolution)
{
    cout<<"--------------------------------------------"<<endl;
    cout<<"Starting Gluttonous Algorithm: \n";
    
    int flag=0;
    steinerForest solutionGraph(nVertex);
    
    // Trivial Clustering and supernodes and terminals:
    
    // (1) For each terminal, creates a terminal node (from the terminal class) by terminal index, its mate index, and true(it is active)
    // (2) Create a supernode S0 ( from supernode class)
    // (3) insert the terminal to the S0.supernodeList
    // (4) supernode is active --->  S0.active=true;
    
    vector<supernode> Clustering;
    for (int i=0; i<pairedTerminals.size(); i++) {
        
        // do the above procedure for the first component of the pair
        supernode S0;
        S0.supernodeList.insert(make_pair(pairedTerminals[i][0],terminal(pairedTerminals[i][0],pairedTerminals[i][1],true)));
        S0.active=true;
        Clustering.push_back(S0);
        
        // do the above procedure for the second component of the pair
        supernode S1;
        S1.supernodeList.insert(make_pair(pairedTerminals[i][1],terminal(pairedTerminals[i][1],pairedTerminals[i][0],true)));
        S1.active=true;
        Clustering.push_back(S1);
    }
    
    //---------------------------------------------------------------------------------------------------------------------
    // Matrices needed for all-shortest path compuation
    vector<vector<int> > terminalsShortestPath;
    vector<int> rows(nVertex,INT_MAX);
    for (int i=0; i<nVertex; i++)
        terminalsShortestPath.push_back(rows);
    
    vector<vector<int>> pathTracker;
    vector<int> rows2(nVertex,-1);
    for (int i=0; i<nVertex; i++)
        pathTracker.push_back(rows2);

    cout<<"****************** Staring the Main Loop ******************"<<endl;
    while (flag==0) {

        // Creating C-puncturing of Metric M
        // using the obtained shortest path, find which two supernodes are closest to connect
        floydWarshall(nVertex, adjList,terminalsShortestPath,pathTracker);
        int minMetricLength=INT_MAX;
        vector<vector<int>> bestPathVector;
        int i_selected=-1;
        int j_selected=-1;
        for (int i=0; i<Clustering.size()-1; i++)
        {
            if(Clustering[i].active!=false)
            {
                unordered_map <int,terminal> :: iterator itr1;
                for (itr1 = Clustering[i].supernodeList.begin(); itr1 != Clustering[i].supernodeList.end(); itr1++)
                {
                    for (int j=i+1; j<Clustering.size(); j++) {
                        unordered_map <int,terminal> :: iterator itr2;
                        for (itr2 = Clustering[j].supernodeList.begin(); itr2 != Clustering[j].supernodeList.end(); itr2++)
                        {
                            int index1= (itr1->second).myIndex;
                            int index2= (itr2->second).myIndex;
                            int dist=terminalsShortestPath[index1][index2];
                            if (dist<minMetricLength)
                            {
                                bestPathVector.clear();
                                minMetricLength=dist; // holds the minimum path between the terminals
                                if (pathTracker[index1][index2]==index1 || pathTracker[index1][index1]==index2) {
                                    vector<int> tempVec;
                                    tempVec.push_back(index1);
                                    tempVec.push_back(index2);
                                    bestPathVector.push_back(tempVec);
                                }
                                else
                                {
                                    int temp1=index1;
                                    int temp2=index2;
                                    while (pathTracker[temp1][temp2]!=temp1) {
                                        vector<int> tempVec;
                                        tempVec.push_back(temp2);
                                        tempVec.push_back(pathTracker[temp1][temp2]);
                                        bestPathVector.push_back(tempVec);
                                        temp2=pathTracker[temp1][temp2];
                                    }
                                    vector<int> tempVec;
                                    tempVec.push_back(temp2);
                                    tempVec.push_back(pathTracker[temp1][temp2]);
                                    bestPathVector.push_back(tempVec);
                                }
                                i_selected=i; // holds which 2 supernodes to merge.
                                j_selected=j;
                            }
                        }
                    }
                }
            }
        }

        for (int i=0; i<bestPathVector.size(); i++) {
            int localW=0;
            for (int j=0; j<adjList[bestPathVector[i][0]].size(); j++) {
                if (adjList[bestPathVector[i][0]][j].first==bestPathVector[i][1]) {
                    localW=adjList[bestPathVector[i][0]][j].second;
                }
            }
            solutionGraph.addEdge(bestPathVector[i][0],bestPathVector[i][1],localW);
            
            vector< pair<int, int> >::iterator j;
            for (j = adjList[bestPathVector[i][0]].begin(); j != adjList[bestPathVector[i][0]].end(); ++j)
            {
                int weight;
                int v = (*j).first;
                if (v==bestPathVector[i][1]) {
                    weight = (*j).second;
                    (*j).second=0;
                }
            }
            for (j = adjList[bestPathVector[i][1]].begin(); j != adjList[bestPathVector[i][1]].end(); ++j)
            {
                int weight;
                int v = (*j).first;
                if (v==bestPathVector[i][0]) {
                    weight = (*j).second;
                    (*j).second=0;
                }
            }
        }
        
        // Merging and updating Clustering (merging and deleting)
        // create a new supernode from supernodes i and j, add it into cluster and then delete i and j from the cluster
        
        supernode S_merged;
        auto merged_supernodes = Clustering[i_selected].supernodeList;
        merged_supernodes.insert(Clustering[j_selected].supernodeList.begin(), Clustering[j_selected].supernodeList.end());
        S_merged.supernodeList=merged_supernodes;
        S_merged.active=false;
        Clustering.push_back(S_merged);
        Clustering.erase(Clustering.begin() + i_selected);
        Clustering.erase(Clustering.begin() + j_selected-1);
        
        // Update Status of supernodes and terminals
        flag=1;
        for (int i=0; i<Clustering.size(); i++)
        {
            int statusFlag=0;
            unordered_map <int,terminal> :: iterator itr;
            for (itr = Clustering[i].supernodeList.begin(); itr != Clustering[i].supernodeList.end(); itr++)
            {
                auto key=(itr->second).myMateIndex; // check if its mate is in the supernode
                if (Clustering[i].supernodeList.find(key)==Clustering[i].supernodeList.end()) // not found its mate
                {
                    statusFlag=1;
                }else // found its mate
                {
                    (itr->second).updateState();
                }
            }
            if (statusFlag==1)  // means that the supernode (Clustering[i]) still is active
                Clustering[i].active=true;
            
            
            if (Clustering[i].active==true)  // means the supernode is still active, so flag it to do one more iteration
                flag=0;
        }
    }
   
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
                    initialSolution+=weight;
                }
            }
        }
    }
    
    for (int i=0; i<pairedTerminals.size(); i++)
    {
        int localSum=0;
        solutionGraph.BFSCleanSolution(pairedTerminals[i][0],pairedTerminals[i][1],localSum);
        cleanedSolution=cleanedSolution+localSum;

    }
    cout<<"The last line of Gluttonous Algorithm \n";
    cout<<"--------------------------------------------"<<endl;
}
