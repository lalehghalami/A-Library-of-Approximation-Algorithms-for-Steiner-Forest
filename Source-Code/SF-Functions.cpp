#include <iostream>
#include <climits>
#include <fstream>
#include <vector>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <list>
#include <queue>
#include <sstream>
#include <string>
#include <string.h>

#include "SF-Functions.h"

using namespace std;

typedef pair<int, int> iPair;

void creatInputPath(string &strInputFile,string path,string nFile)
{
    string  strInput_0, strInput_1, strInput_2;
    
    strInputFile.append(path);
    strInputFile.append(nFile);
}
void creatOutputPath(string &strOutputFile, string nFile, string alg, string run)
{
    string  strOutput_0, strOutput_1, strOutput_2, strOutput_3,strOutput_F;
    
    strOutput_0 ="Result-Alg-";
    strOutputFile.append(strOutput_0);
    strOutputFile.append(alg);
    strOutput_2="-Instance";
    strOutputFile.append(strOutput_2);
    strOutputFile.append(nFile);
    
    strOutput_3="-run";
    strOutputFile.append(strOutput_3);
    strOutputFile.append(run);
    strOutput_F=".txt";
    strOutputFile.append(strOutput_F);

    cout<<"Run : "<< run<<endl;   
}

void readInputFileToAdjMatrix(string str, int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<vector<int> > & adjMatrix, vector<vector<int > > & sites, vector<vector<int > > & E, double &prob, double &avEdges)
{
    sites.clear();
    ifstream myfile;
    myfile.open(str);
    if(!myfile)
    {
        cout << "Error: file could not be opened"  << endl;
        exit (EXIT_FAILURE);
    }
    
    static const int max_line = 65536;
    string s;
    myfile.ignore(max_line, '\n');
    myfile>>s; // Nodes;
    myfile>>nVertex;
    myfile>>s; // Edges;
    myfile>>nEdges;
    
    vector<int> tempAdjVec (nVertex,0);
    for (int i=0; i<nVertex; i++)
        adjMatrix.push_back(tempAdjVec);
    
    int i1,i2,w;
    myfile>>s;
    while (s=="E") {
        myfile >> i1 >> i2 >> w;
        adjMatrix[i1-1][i2-1]=w;
        adjMatrix[i2-1][i1-1]=w;
        vector<int> edge;
        edge.push_back(i1-1);
        edge.push_back(i2-1);
        E.push_back(edge);
        myfile>>s;
        if (s=="END") break;
    }
    
    myfile.ignore(max_line, '\n');
    myfile>>s; // SECTION;
    myfile>>s; // Terminals;
    myfile>>s; // Terminals;
    myfile>>nTerminals; // nTerminals;
    terminals=new int[nTerminals];
    myfile>>s; // T;
    
    int counter=1;
    int tIndex=0;
    
    int t1,t2;
     while (s=="TP")
    {
	myfile >> t1 >> t2;
	terminals[tIndex]=t1-1;
	tIndex++;
        terminals[tIndex]=t2-1;
	tIndex++;
	vector<int> terComponent;
	terComponent.push_back(t1-1);
	terComponent.push_back(t2-1);
	sites.push_back(terComponent);
        myfile>>s;
        if (s=="END") break;
    }

}

void readInputFileAdjList(string str, int &nVertex, int &nEdges, int &nTerminals, int *&terminals, vector<pair<int,int> > *&adj, vector<vector<int > > & sites, vector<vector<int > > & E,double &prob, double &avEdges)
{
    ifstream myfile;
    myfile.open(str);
    if(!myfile)
    {
        cout << "Error: file could not be opened"  << endl;
        exit (EXIT_FAILURE);
    }
    
    static const int max_line = 65536;
    string s;
    myfile.ignore(max_line, '\n');
    myfile>>s; // Nodes;
    myfile>>nVertex;
    myfile>>s; // Edges;
    myfile>>nEdges;
    
    adj = new vector<pair<int,int> >[nVertex];
    int a1,a2,a3;
    myfile>>s;
    while (s=="E") {
        myfile >> a1 >> a2 >> a3;
        adj[a1-1].push_back(make_pair(a2-1,a3));
        adj[a2-1].push_back(make_pair(a1-1,a3));
        vector<int> edge;
        edge.push_back(a1-1);
        edge.push_back(a2-1);
        E.push_back(edge);
        
        
        myfile>>s;
        if (s=="END") break;
    }
    
    myfile.ignore(max_line, '\n');
    myfile>>s; // SECTION;
    myfile>>s; // Terminals;
    myfile>>s; // Terminals;
    myfile>>nTerminals; // nTerminals;
    terminals=new int[nTerminals];
    myfile>>s; // T;
    
    int counter=1;
    int tIndex=0;
    

   int	t1,t2;
     while (s=="TP")
    {
        myfile >> t1 >> t2;
        terminals[tIndex]=t1-1;
        tIndex++;
       	terminals[tIndex]=t2-1;
        tIndex++;
        vector<int> terComponent;
        terComponent.push_back(t1-1);
        terComponent.push_back(t2-1);
        sites.push_back(terComponent);
        myfile>>s;
        if (s=="END") break;
    }
    
}


//// *************************************************************************//
int dijkstraWithAdjMatrix(int source, int sink,int nVertex, vector<vector<int> > &adjMatrix, vector<vector< int > > &path)
{
    
    vector<int> dist(nVertex, INT_MAX);
    dist[source]=0;
    
    int* visited=new int[nVertex];
    memset(visited, 0, nVertex*sizeof(int));
    
    int* prev=new int[nVertex];
    prev[source]=source;
    
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;        // Create a priority queue to store vertices that are being preprocessed.
    pq.push(make_pair(0,source));                                       // Insert source itself in priority queue and initialize its distance as 0.
    
    int u;
    while (!pq.empty())
    {
        u=pq.top().second;
        pq.pop();
        vector< pair<int, int> >::iterator i;
        
        for (int j=0; j<nVertex; j++) {
            if (adjMatrix[u][j]!=0) {
                int v=j;
                int weight=adjMatrix[u][j];
                
                if (dist[v]>dist[u]+weight)
                {
                    dist[v]=dist[u]+weight;
                    pq.push(make_pair(dist[v],v));
                    prev[v]=u;
                }
                
            }
        }
        
       
        
    }
    
    int flag=0;
    int temp=sink;
    while (flag==0) {
        vector<int> tempVec;
        tempVec.push_back(temp);
        tempVec.push_back(prev[temp]);
        path.push_back(tempVec);
        if (prev[temp]==source) flag=1;
        temp=prev[temp];
    }
    return dist[sink];
}
int dijkstra(int source, int sink,int nVertex, vector<pair<int,int> > *&adjList, vector<vector< int > > &path)
{
    
    vector<int> dist(nVertex, INT_MAX);
    dist[source]=0;
    
    int* visited=new int[nVertex];
    memset(visited, 0, nVertex*sizeof(int));
    
    int* prev=new int[nVertex];
    prev[source]=source;
    
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;        // Create a priority queue to store vertices that are being preprocessed.
    pq.push(make_pair(0,source));                                       // Insert source itself in priority queue and initialize its distance as 0.
    
    int u;
    while (!pq.empty())
    {
        u=pq.top().second;
        pq.pop();
        vector< pair<int, int> >::iterator i;
        for (i = adjList[u].begin(); i != adjList[u].end(); ++i){       // Get vertex label and weight of current adjacent of u.
            int v = (*i).first;
            int weight = (*i).second;
            
            if (dist[v]>dist[u]+weight)
            {
                dist[v]=dist[u]+weight;
                // ?? Before addding to PQ need to check if already added this node, if so needs to update it other than add a new duplicate (visited vector) !
                pq.push(make_pair(dist[v],v));
                prev[v]=u;
            }
        }
        
    }
    
    int flag=0;
    int temp=sink;
    while (flag==0) {
        vector<int> tempVec;
        tempVec.push_back(temp);
        tempVec.push_back(prev[temp]);
        path.push_back(tempVec);
        if (prev[temp]==source) flag=1;
        temp=prev[temp];
    }
    return dist[sink];
}

// *************************************************************************//
// Tree Metric Functions
int findPath(vector<pair<int,int> > *&adjList ,vector<vector<int > > & pathMatrix, int nVertex){
    vector<vector<int > > Matrix;
    
    vector<int> rows(nVertex,INT_MAX);
    for (int i=0; i<nVertex; i++)
        Matrix.push_back(rows);
    
    for (int  i=0; i<nVertex; i++) {
        vector< pair<int, int> >::iterator z;
        for (z = adjList[i].begin(); z != adjList[i].end(); ++z){       // Get vertex label and weight of current adjacent of u.
            int v = (*z).first;
            int weight = (*z).second;
            Matrix[i][v] = weight;
        }
    }
    
    
    pathMatrix.clear();
    for ( int j = 0 ; j < nVertex  ; j++ )
    {
        vector<int> tempCopy;
        for ( int k = 0 ; k < nVertex ; k++ )
        {
            tempCopy.push_back(Matrix[j][k]);
        }
        pathMatrix.push_back(tempCopy);
    }
    
    int diam=0;
    for ( int j = 0 ; j < nVertex  ; j++ )           // Set diagonal to 0
        pathMatrix[j][j]= 0;
    
    for ( int m = 0 ; m < nVertex  ; m++ )           // Compute paths
        for ( int j = 0 ; j < nVertex  ; j++ )
            for ( int k = 0 ; k < nVertex ; k++ )
                if ( long(pathMatrix[j][m]) + pathMatrix[m][k] < pathMatrix[j][k] )
                    pathMatrix[j][k]= pathMatrix[j][m] + pathMatrix[m][k];
    
    for ( int i = 0 ; i < nVertex  ; i++ )           // Compute diam
        for ( int j = 0 ; j < nVertex  ; j++ )
            if (pathMatrix[i][j]>diam) {
                diam=pathMatrix[i][j];
            }
    
    return diam;
}
// *************************************************************************//


int pow2roundup (int x)
{
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}

// *************************************************************************//

vector<int> intersection(vector<int> &v1, vector<int> &v2)
{
    vector<int> v3;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    return v3;
}
// *************************************************************************//

void floydWarshall (int &nVertex, vector<pair<int,int> > *&adjList,vector<vector<int > > & distResult,vector<vector<int > > & pathTracker)
{
    
    int  i, j, k;
    
    for (i = 0; i < nVertex; i++)
        for (j = 0; j < nVertex; j++)
        {
            distResult[i][j] = INT_MAX;
            pathTracker[i][j] = -1;
        }
    
    for ( i=0; i<nVertex; i++) {
        vector< pair<int, int> >::iterator z;
        for (z = adjList[i].begin(); z != adjList[i].end(); ++z){       // Get vertex label and weight of current adjacent of u.
            int v = (*z).first;
            int weight = (*z).second;
            distResult[i][v] = weight;
            pathTracker[i][v] = i;
        }
    }
    for (i = 0; i < nVertex; i++)
        distResult[i][i]=0;
    
    for (k = 0; k < nVertex; k++)
    {
        for (i = 0; i < nVertex; i++)
        {
            for (j = 0; j < nVertex; j++)
            {
                
                if ((!(distResult[i][k]==INT_MAX))&&(!(distResult[k][j]==INT_MAX)))
                    if (long(distResult[i][k] + distResult[k][j] < distResult[i][j]))
                    {
                        distResult[i][j] = distResult[i][k] + distResult[k][j];
                        pathTracker[i][j] = pathTracker[k][j];
                    }
            }
        }
    }
    
}
