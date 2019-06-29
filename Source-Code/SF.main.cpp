#include <time.h>
#include <sys/time.h>

#include "SF-Solution.h"
#include "SF-Functions.h"
#include "PG-SF.hpp"
#include "GL-SF.hpp"
#include "PD-SF.hpp"
#include "TM-SF.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // Defining variables:
    string nFile,alg,strInputFile,strOutputFile,path;
    int nVertex,nEdges,nTerminals;
    vector<pair<int,int>> *adjList;
    int *terminals;
    vector<vector<int> > pairedTerminals;
    struct timeval time_start,time_end;
    double durationAlg;
    int initialSolution=0;
    int cleanedSolution=0;
    
    if(argc<6)
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
    }
    
    // Input and Output Files path
    creatInputPath(strInputFile,path,nFile);
    readInputFileAdjList(strInputFile, nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals);
    
    cout<<"********************* File  "<<nFile<<"  is read. ********************** \n";

    
    creatOutputPath(strOutputFile,nFile,alg);
    ofstream outputFile;
    outputFile.open(strOutputFile);

    if (alg=="PG")
    {
        cout<<"Calling Paird Greedy Algorithm \n";
        gettimeofday(&time_start, NULL);
        greedyAlgorithm(nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, cleanedSolution, initialSolution);
        gettimeofday(&time_end, NULL);
    }
    else if (alg=="PD")
    {
        cout<<"Calling Primal Dual Algorithm \n";
        gettimeofday(&time_start, NULL);
        PrimalDualAlgorithm(nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, cleanedSolution,initialSolution);
        gettimeofday(&time_end, NULL);
    }
    else if (alg=="GL")
    {
        cout<<"Calling Gluttonous Algorithm \n";
        gettimeofday(&time_start, NULL);
        gluttonousAlgorithm(nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, cleanedSolution, initialSolution);
        gettimeofday(&time_end, NULL);
    }
    else if (alg=="TM")
    {
        cout<<"Calling Tree Metric Algorithm \n";
        gettimeofday(&time_start, NULL);
        treeMetricAlgorithm(nVertex, nEdges, nTerminals, terminals, adjList, pairedTerminals, cleanedSolution);
        gettimeofday(&time_end, NULL);
        
    }else
    {
        cout<<"The requested algorithm is not recegnized \n";
    }
    
    cout<<"Computing the solution is complete! \n";
    cout<<"--------------------------------------------"<<endl;
    durationAlg = (time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec);
    
    // Output:
    outputFile<< nFile<<"\n"<<nVertex<<"\n"<<nEdges<<"\n"<<nTerminals<<"\n";
    outputFile<< initialSolution<<"\n"<<cleanedSolution<<"\n"<<durationAlg<<endl;
    cout<<"******************************************************************** \n";

    return 0;
}

// Creating path for input
//     string strInput_0= "/data/wsuhome/ff/ff96/ff9687/Forest-Instances-Parameterized/instance";
// Creating path for output
//    string strO0="/wsu/home/ff/ff96/ff9687/Results-7Apr/Result-Alg-";
//        string strO0="/Users/lghalami/Documents/Laleh/Steiner/code/Result-Alg-";
//    string strO0="/Users/lalehghalami/Desktop/SF-test/Result-Alg-";

