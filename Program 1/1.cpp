// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define V 100

typedef struct
{
 int from;
 int to;
 double flowValue;
}arrange;
 
arrange A[V*V];
int n=0;
int e=0;
int count=0;
double rGraph[V][V];
double maxflow[V][V];
double graph[V][V];
/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(double rGraph[V][V], int s, int t, int parent[V][V],int pathNumber)
{
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[pathNumber][s] = -1;
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=1; v<=n; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[pathNumber][v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 
// Returns tne maximum flow from s to t in the given graph
double fordFulkerson(int s, int t,double demand)
{
    int u, v;
    int parent[V][V];  // This array is filled by BFS and to store path
    int pathNumber=1;
    double max_flow = 0;  // There is no flow initially
    double path_flow[V];
   
    for(int i=0;i<V;i++)
	path_flow[i]=99999.0;

    double tempGraph[V][V];   //copy residual graph into a temporary graph before making changes
    double tempflow[V][V];

    for(u=1;u<=n;u++)
	for(v=1;v<=n;v++)
	{
		tempflow[u][v]=maxflow[u][v];
		tempGraph[u][v]=rGraph[u][v];
	}

 
    // Augment the flow while tere is path from source to sink
    while (demand!=0&&bfs(rGraph, s, t, parent,pathNumber))
    {
        // Find minimum residual capacity of the edhes along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        for (v=t; v!=s; v=parent[pathNumber][v])
        {
            u = parent[pathNumber][v];
            path_flow[pathNumber] = min(path_flow[pathNumber], rGraph[u][v]);
        }

        // Add path flow to overall flow
        max_flow += path_flow[pathNumber];
 	if(path_flow[pathNumber]>demand)
	{
                // update residual capacities of the edges and reverse edges along the path
		for (v=t; v != s; v=parent[pathNumber][v])
		{
		    u = parent[pathNumber][v];
		    rGraph[u][v] -= demand;
		    maxflow[u][v]+=demand;
		    //maxflow[v][u]-=demand;
		    rGraph[v][u] += demand;
		}
		demand=0;
	}
	else
	{
        	demand-=path_flow[pathNumber];
		for (v=t; v != s; v=parent[pathNumber][v])
		{
		    u = parent[pathNumber][v];
		    rGraph[u][v] -= path_flow[pathNumber];
		    maxflow[u][v]+=path_flow[pathNumber];
		    //maxflow[v][u]-=path_flow[pathNumber];
		    rGraph[v][u] += path_flow[pathNumber];
		}
		
	}
        pathNumber++;
    }
    if(demand==0)
	return max_flow;
    else  //restore changes made to rgraph.
    {
      	for(u=1;u<=n;u++)
		for(v=1;v<=n;v++)
		{
			maxflow[u][v]=tempflow[u][v];
			rGraph[u][v]=tempGraph[u][v];
		}
	return 0;
    }	
    
}

int bestcmp(const void *x, const void *y)
{
   return ( (*(arrange*)x).flowValue - (*(arrange*)y).flowValue );
}

void printResult()
{
 printf("From\t To\t TotalFlow \n");
 for(int i=0;i<count;i++)
 	printf("%d\t %d\t %lf\n",A[i].from,A[i].to,A[i].flowValue);
}
 
// Driver program to test above functions
int main(int argc,char *argv[])
{
    char *inputFile,*demandFile;
    char c;
    int demand,instance=0;
    int from,to=0;
    int f=0,nf=0;
    int source,sink;
    double cost[V][V];
    int u,v=0;
    int node=0,instanceFlag=0;


     if(argc<4)
    {
     printf("Usage: ./1 input_file.txt demand_file.txt instance_number [inNode/outNode] \n");
     exit(0);
    }

    inputFile=argv[1];
    demandFile=argv[2];
    instance=atoi(argv[3]);

    if(instance==1||instance==2)
    {
	node=atoi(argv[4]);
	instanceFlag=12;
    }
    else if(instance==3||instance==4)
    {
	node=atoi(argv[4]);
	instanceFlag=345;
    }
    else if(instance==5)
    {
    	instanceFlag=345;
    }
    else if(instance==100)
    {
  	instanceFlag=100;
    }  

    for (u = 1; u <= n; u++)
        	for (v = 1; v <= n; v++)
             		graph[u][v] = 0;

    FILE *input=fopen(inputFile,"r");
    
    for (c = getc(input); c != EOF; c = getc(input))
        if (c == '\n') // Increment count if this character is newline
            e = e + 1;
    fclose(input);
    e=e-1;

    input=fopen(inputFile,"r");
    fscanf(input,"%d",&n);

	    
for(int edge=1;edge<=e;edge++)
{
 double capacity=0.0,price=0.0;
 fscanf(input,"%d %d %lf %lf",&from,&to,&price,&capacity);
 graph[from][to]=capacity;
 cost[from][to]=price;
}
fclose(input);
    
    for (u = 1; u <= n; u++)
        for (v = 1; v <= n; v++)
	{
	     maxflow[u][v]=0;
             rGraph[u][v] = graph[u][v];
	}

    FILE *demands=fopen(demandFile,"r");
    e=0;
    for (c = getc(demands); c != EOF; c = getc(demands))
        if (c == '\n') // Increment count if this character is newline
            e = e + 1;
    fclose(demands);

    demands=fopen(demandFile,"r");
    fscanf(demands,"%d",&n);
    e=e-1;

    double flow=0.0;
    for(int edge=1;edge<=e;edge++)
    {
     int to,from;
     double demand=0.0;
     fscanf(demands,"%d %d %lf",&from,&to,&demand);
     flow=fordFulkerson(from,to,demand);
     //maxflow[from][to]=flow;
     if(flow>0)
	f++;
     else
	nf++;
    }
 
    double flowin=0.0;
    double max=0.0;

    if(instance==5)
    {
    for(u=1;u<=n;u++)
    {
 	for(v=1;v<=n;v++)
	{
	 flowin+=maxflow[v][u];
	}
	if(flowin>max)
	{
	  max=flowin;
	  node=u;
	}
	flowin=0.0;
    }
	printf("The node which has the maximum inflows is : Node %d\n",node);
    }

    if(f==e)
   {
     printf("The given flow is feasible \n");
     for(v=1;v<=n;v++)
    {
     if(graph[v][node]>0&&instanceFlag==345)
	printf("Total flow on incoming link from Node %d to Node %d : %lf\n",v,node,maxflow[v][node]);
     if(graph[node][v]>0&&instanceFlag==12)
	printf("Total flow of outgoing link from Node %d to Node %d : %lf\n",node,v,maxflow[node][v]);
    }
   }
   else
 	printf("The given flow is NOT feasible \n");

        printf("\nNetwork Flow Summary\n");
      	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(graph[i][j]!=0)
			{
				A[count].from=i;
				A[count].to=j;
				A[count].flowValue=maxflow[i][j];
				count++;
			}
		
		}
	}
        qsort(A,count,sizeof(arrange),bestcmp);
        printResult();
    fclose(demands);
    return 0;
}
