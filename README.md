# Approximation Algorithms for Steiner Forest: An Experimental Study

In the Steiner Forest problem, we are given a set of terminal pairs and need to find
the minimum cost subgraph that connects each of the terminal pairs together. Motivated by the
recent work on greedy approximation algorithms for the Steiner Forest, we provide efficient implementations of
existing approximation algorithms and conduct a thorough experimental study to characterize their performance.
We consider several approximation algorithms: the influential primal-dual 2-approximation algorithm due to
Agrawal, Klein and Ravi, the greedy algorithm due to Gupta and Kumar, and a randomized
algorithm based on probabilistic approximation by tree metrics. We also consider the simplest heuristic
greedy algorithm for the problem, which picks the closest unconnected pair of terminals and connects it using the
shortest path between the terminals in the current graph. Our analysis reveals that for the majority of 
instances with a small number of terminals the heuristic greedy algorithm has the smallest 
running times and obtains solutions that are close to or better than the solutions obtained by 
the other algorithms. For instances with a large number of terminals and a large
number of edges, the algorithm based on probabilistic approximation by tree metrics has the smallest running time
and obtains solutions that have costs closer to the solutions obtained by the other algorithms. 


## Getting Started

The package contains three folders "SF-Source-Codes", "SF-Samples", and "SF-Results". "SF-Source-Codes" includes source codes and makefile and jobscript to test the instances. "SF-Results" is an empty folder that the results of the test will be stored in. "SF-Samples" includes three different groups of samples corresponding to the test samples in the paper. 

### SF-Source-Codes

This folder cotains all source codes, makefile and jobscript to test all samples. 

The main file "SF-main.cpp" reads the input and calls each algorithm. All the required functions for different algorithms to calculate the solution are located in "SF-Functions.cpp" and "SF-Functions.h". The solution graph is defined in "SF-Solution.cpp" and "SF-Solution.h". The rest of the files corresponding to codes for each algorithm:

"PD-SF.cpp" and "PD-SF.hpp"   -> Primal-Dual Algorithm 
"PG-SF.cpp" and "PG-SF.hpp"   -> Paired Greedy Algorithm
"GL-SF.cpp" and "GL-SF.hpp"  -> Gluttonous Algorithm 
"TM-SF.cpp", "TM-SF.hpp", "TM-Functions.cpp" and "TM-Functions.h"  -> Tree Metrics Algorithm



### SF-Samples

"SF-Samples" contains there folders which correspond to different experiments. 
"SF-Instances-NM" contains 24 instances related to Figure xx to Figure xx in the paper 
in which we investigate the impact of the number of vertices (n) and the number of edges (m). 
The next file is "SF-Instances-different-t", which contains 16 instances. For these instances 
we considered the effect of the number of the terminals on the algorithms' performance. 
The third file is "SF-Instances-OPT" that contains the instances for which we obtained 
the optimal solution for them. 
The following tables show each group instances with their specifications. 

Samples in "SF-Instances-NM" Folder:

File name                n           m            t
instance-nm-001    2500    62500      6
instance-nm-002    640      960          10
instance-nm-003    640      4135        10
instance-nm-004    640      204480    10
instance-nm-005    777      1239        10
instance-nm-006    875      1522        10
instance-nm-007    1290    2270        10
instance-nm-008    2500    5000        10
instance-nm-009    3221    5938        10
instance-nm-010    2500    12500      10
instance-nm-011    572      963          12
instance-nm-012    1981    3633        12
instance-nm-013    933      1632        14
instance-nm-014    1359    2458        14
instance-nm-015    1196    2084        14
instance-nm-016    712      1217        16
instance-nm-017    1051    1791        16
instance-nm-018    1848    3286        16
instance-nm-019    2039    3548        18
instance-nm-020    493      963          24
instance-nm-021    2213    4135        26
instance-nm-022    640      40896      26
instance-nm-023    1724    2975        30
instance-nm-024    2132    3702        38

Samples in "SF-Instances-different-t" Folder:

File name                   n         m             t
isntance-t-001-10      640    204480    10
isntance-t-001-50      640    204480    50
isntance-t-001-80      640    204480    80
isntance-t-001-100    640    204480    100
isntance-t-001-150    640    204480    150
isntance-t-001-200    640    204480    200
isntance-t-001-250    640    204480    250
isntance-t-001-300    640    204480    300
isntance-t-002-26      640    40896      26
isntance-t-002-50      640    40896      50
isntance-t-002-80      640    40896      80
isntance-t-002-100    640    40896      100
isntance-t-002-150    640    40896      150
isntance-t-002-200    640    40896      200
isntance-t-002-250    640    40896      250
isntance-t-002-300    640    40896      300

Samples in "SF-Instances-OPT" Folder:

File name           n        m       t     
instance-opt-001    53       80      4
instance-opt-002    157      266     6
instance-opt-003    57       84      8
instance-opt-004    64       288     8
instance-opt-005    90       135     10
instance-opt-006    179      293     10
instance-opt-007    298      503     10
instance-opt-008    331      560     10
instance-opt-009    128      227     12
instance-opt-010    191      302     12
instance-opt-011    237      390     12
instance-opt-012    278      478     12
instance-opt-013    353      608     12
instance-opt-014    64       192     12
instance-opt-015    233      386     12
instance-opt-016    386      653     12
instance-opt-017    110      188     14
instance-opt-018    165      274     14
instance-opt-019    193      369     16
instance-opt-020    122      194     18
instance-opt-021    220      374     18
instance-opt-022    211      380     18
instance-opt-023    189      353     20

## Running the tests

In this section we explain how to run the tests. 
In order to start the test, you need to set two path variables, which we 
defined in "jobscript" at "SF-Source-Codes" folder, as follows:

```
inPath=/... local directory.../jea-acm-SF-Materials/SF-Samples/  # replace the directory of Samples
outPath=/... local directory.../jea-acm-SF-Materials/SF-Results/ # replace the Results directory
```
"jobscript" contains different samples for all the algorithms. For example, the following 
command line runs the program for the first sample folder "SF-Instances-NM", and solve the 
problem with primal dual algorithm (PD). 

```
./SFout $inPath $outPath $file1 -nm-001 PD
```
After setting "inPath" and "outPath" variables in "jobscript", you are ready to test the software. 
Set your local directory to "SF-Source-Codes", apply the following command lines:

```
$ make
$ sh jobscript

```
Then all tests will be run automatically, and outputs will be stored in "SF-Results" Folder. 

### How to read results

Outputs are in text format with suggestive file names. For example: "Result-Alg-PD-Instance-nm-001" 
Means the result file corresponds to sample "001" sample folder "SF-Instances-NM", 
and it shows the results of "PD" (Primal Dual Algorithm). Each result file contains 
"File label", "number of vertices", "number of edges", "number of executed iterations", 
"initial solution", "cleaned solution", and "the algorithm time spending(microseconds)", 
respectively. The following example shows the result for a sample file with label 
"-nm-001", 2500 vertices and 62500 edges, the PD algorithm performed 6 iterations 
and the initial solution is 492, after cleaning the solution cost is dropped to 17. 
The algorithm duration including reading input file is 187630 micro seconds, or 0.18 seconds. 

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
