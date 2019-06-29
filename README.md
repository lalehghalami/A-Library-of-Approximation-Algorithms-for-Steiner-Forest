# A-Library-of-Approximation-Algorithms-for-Steiner-Forest
In the Steiner Forest problem, we are given a set of terminal pairs and need to find the minimum cost subgraph that connects each of the terminal pairs together. Motivated by the recent work on greedy approximation algorithms for the Steiner Forest, we provide efficient implementations of existing approximation algorithms and conduct a thorough experimental study to characterize their performance. We consider several approximation algorithms: the influential primal-dual 2-approximation algorithm due to Agrawal, Klein and Ravi, the greedy algorithm due to Gupta and Kumar, and a randomized algorithm based on probabilistic approximation by tree metrics. We also consider the simplest heuristic greedy algorithm for the problem, which picks the closest unconnected pair of terminals and connects it using the shortest path between the terminals in the current graph. Our analysis reveals that for the majority of instances the heuristic greedy algorithm has the smallest running times and obtains solutions that are close to or better than the solutions obtained by the other algorithms. For instances with a large number of terminals and a large number of edges, the algorithm based on probabilistic approximation by tree metrics has the smallest running time and obtains solutions that have costs closer to the solutions obtained by the other algorithms.

## Getting Started
"Source-Code" includes source codes and makefile and jobscript to test the instances. 

### Source-Code

This folder cotains all source codes, makefile and jobscript to test all samples. 

The main file "SF-main.cpp" reads input and calls each algorithm to perform calculation. All the requied functions for different algorithms to calculate the solution are located in "SF-Functions.cpp" and "SF-Functions.h". The solution graph is a structed graph that we defined in "SF-Solution.cpp" and "SF-Solution.h". The rest of the files do the specific calcuclations corresponding to each algorithm:

"PD-SF.cpp" and "PD-SF.hpp"   -> Primal Dual Algorithm 
"PG-SF.cpp" and "PG-SF.hpp"   -> Paird Greedy Algorithm
"GL-SF.cpp" and "GL-SF.hpp"  -> Glotonouse Algorithm 
"TM-SF.cpp", "TM-SF.hpp", "TM-Functions.cpp" and "TM-Functions.h"  -> Tree Metrics Algorithm


## Running the tests

In this section we explain how run the automated tests for this system. 
In order to start the test, you need to set two path variables, which we defined in "jobscript" at "SF-Source-Codes" folder, as follows:

```
inPath=/... local directory.../jea-acm-SF-Materials/SF-Samples/  # replace the directory of Samples
outPath=/... local directory.../jea-acm-SF-Materials/SF-Results/ # replace the Results directory
```
"jobscript" contains all differents samples for all differents algorithms. For example following command line runs the program for the first ample folder "SF-Instances-NM", and solve the problem with primal dual algorithm (PD). 

```
./SFout $inPath $outPath $file1 -nm-001 PD
```
Afetr setting "inPath" and "outPath" variables in "jobscript", you are ready to test the system. Set your local directory to "SF-Source-Codes", apply following command lines:

```
$ make
$ sh jobscript

```
Then all tests will be run automatically, and outputs will be stored in "SF-Results" Folder. 

### How to read results

Outputs are in text format with systemactic file name. For example: "Result-Alg-PD-Instance-nm-001" Means the result file is corresponding with sample "001" sample folder "SF-Instances-NM", and it shows the results of "PD" (Primal Dual Algorithm). Each result file contains "File label", "number of vertices", "number of edges", "number of exectued iterations", "initial solution", "cleaned solution", and "the algorithm time spending(microseconds)", respectively. Following example shows the result for a sample file with label "-nm-001", 2500 vertices and 62500 edges, the PD algorithm performed 6 iterations and the initial solution is 492, after cleaning the solution cost is dropped to 17. The algorithm duration including reading input file is 187630 micro seconds, or 0.18 seconds. 

```
Result-Alg-PD-Instance-nm-001.txt : 

-nm-001
2500
62500
6
492
17
187630```
```

## Authors

* **Laleh Ghalami** (laleh.ghalami@wayne.edu)
* **Daniel Grosu**   (dgrosu@wayne.edu)
