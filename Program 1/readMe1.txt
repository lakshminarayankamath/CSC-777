PROBLEM STATEMENT: 

Given a set of input and demand files (input+demand=instance), find if the flow is feasible and alsofind the following:
>Flow out of node 8 on each of it's outgoing link.(Instance 1,2)
>Flow into node 14 on each of it's incoming links. (Instance 3,4)
>Which node has the maximum inflow? (Instance 5)

-----------------------------------------------------------------
Compiling Program 1:
g++ -g -o 1 1.cpp

Running Program 1:
./1 inputFileName.txt demandFileName.txt instanceNumber [inNode/outNode]

-----------------------------------------------------------------
Example:
Executing instance 1:
./1 input1.txt demand1.txt 1 8

Executing instance 2:
./1 input2.txt demand2.txt 2 8

Executing instance 3:
./1 input3.txt demand3.txt 3 14

Executing instance 4:
./1 input4.txt demand4.txt 4 14

Executing instance 5:
./1 input5.txt demand5.txt 5 

