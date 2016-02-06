PROBLEM STATEMENT:

Given a set of input and demand files (input+demand=instance), Write a CPLEX program (or a program to create a file that is readable by CPLEX) to find the minimum cost for sending the flow and also find the following:
>Flow out of node 8 on each of it's outgoing link.(Instance 1,2)
>Flow into node 14 on each of it's incoming links. (Instance 3,4)
>Which node has the maximum inflow? (Instance 5)
-----------------------------------------------------------------

STEP 1: Compiling CPP program
g++ -g -o 3 3.cpp

STEP 2: Running CPP program to generate LP file
./3 inputFileName demandFileName

STEP 3: Running the .lp file in CPLEX
a) Login into "CSC495 MFMS fall2015" environment.
b) Paste the generated .lp file.
c) Type the following set of commands (without quotes) in order to get the final optimized output. 

-> "add ilog"
-> "cplex"       [this should get you into the cplex shell]
-> "read LPfileName.lp"
-> "optimize"
-> "display solution variables *"
