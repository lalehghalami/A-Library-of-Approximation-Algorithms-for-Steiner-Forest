#include <time.h>
#include <sys/time.h>
#include <sstream>
#include <string>
#include <string.h>

#include "SF-Solution.h"
#include "SF-Functions.h"
#include "PG-SF.hpp"
#include "GL-SF.hpp"
#include "PD-SF.hpp"
#include "TM-SF.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    
    string nFile,alg,strInputFile,strOutputFile,path,run;
    double prob=0;
    double avEdges=0;
    int nVertex,nEdges,nTerminals;
    vector<pair<int,int>> *adjList;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> E;
    int *terminals;
    vector<vector<int> > pairedTerminals;
    struct timeval time_start,time_end;
    double durationAlg;
    int initialSolution=0;
    int cleanedSolution=0;
    int diameter=0;    
    if(argc<7)
    {
        cout << "Not enough parameters have been passed. \n";
        cin.get();
        exit(0);
    }
    else
    {
        strInputFile=argv[1];
        strOutputFile=argv[2];
        path=argv[3];
        
	nFile=argv[4];
        alg=argv[5];
	run=argv[6];
    }
    
    
    creatInputPath(strInputFile,path,nFile);
    creatOutputPath(strOutputFile,nFile,alg,run);

	cout<<"strInputFile: "<<strInputFile<<endl;
	cout<<"strOutputFile: "<<strOutputFile<<endl;

    ofstream outputFile;
    outputFile.open(strOutputFile);
    
    
    
    if (alg=="PG")
    {
        readInputFileAdjList(strInputFile, nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, E,prob, avEdges);
        gettimeofday(&time_start, NULL);
        cout<<"********************* File  "<<nFile<<"  is read for PG Algorithm. ********************** \n";
        cout<<"Calling Paird Greedy Algorithm \n";
        
        greedyAlgorithm(nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, cleanedSolution, initialSolution);
    }
    else if (alg=="PD")
    {
        
        readInputFileToAdjMatrix(strInputFile, nVertex, nEdges, nTerminals, terminals, adjMatrix, pairedTerminals, E,prob, avEdges);
        gettimeofday(&time_start, NULL);
        cout<<"********************* File  "<<nFile<<"  is read for PD algorithms. ********************** \n";
        cout<<"Calling Primal Dual Algorithm \n";
        
        PrimalDualAlgorithm(nVertex, nEdges, nTerminals, terminals, adjMatrix, pairedTerminals, E,cleanedSolution,initialSolution);
    }
    else if (alg=="PDNoPQ")
    {
        readInputFileToAdjMatrix(strInputFile, nVertex, nEdges, nTerminals, terminals, adjMatrix, pairedTerminals, E,prob, avEdges);
        gettimeofday(&time_start, NULL);
        cout<<"********************* File  "<<nFile<<"  is read for PD-No-PQ algorithms. ********************** \n";
        cout<<"Calling Primal Dual No PQ Algorithm \n";
        PrimalDualAlgorithmNoPQ(nVertex, nEdges, nTerminals, terminals, adjMatrix, pairedTerminals, E,cleanedSolution,initialSolution);
	cout<<"m="<<nEdges<<endl;
	cout<<"T="<<nTerminals<<endl;        
        
    }
    else if (alg=="GL")
    {
        readInputFileAdjList(strInputFile, nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, E,prob, avEdges);
        gettimeofday(&time_start, NULL);
        cout<<"********************* File  "<<nFile<<"  is read for GL Algorithm. ********************** \n";
        cout<<"Calling Gluttonous Algorithm \n";
        gluttonousAlgorithm(nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, cleanedSolution, initialSolution);
        
    }
    else if (alg=="TM")
    {
        readInputFileAdjList(strInputFile, nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, E,prob, avEdges);
        gettimeofday(&time_start, NULL);
        cout<<"********************* File  "<<nFile<<"  is read for TM Algorithm. ********************** \n";
        cout<<"Calling Tree Metric Algorithm \n";
        treeMetricAlgorithm(nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, cleanedSolution, diameter);
        
    }else
    {
        cout<<"The requested algorithm is not recegnized \n";
    }
    gettimeofday(&time_end, NULL);
    
    cout<<"Computing the solution is complete! \n";
    cout<<"--------------------------------------------"<<endl;
    durationAlg = (time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec);
    
    // Output:
    outputFile<< nFile<<"\n"<<nVertex<<"\n"<<nEdges<<"\n"<<nTerminals<<"\n";
    outputFile<< initialSolution<<"\n"<<cleanedSolution<<"\n"<<durationAlg<<"\n"<<diameter<<endl;
    cout<<"******************************************************************** \n";
    
    return 0;
}

