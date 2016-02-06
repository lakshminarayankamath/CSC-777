#include<stdio.h>
#include<stdlib.h>
#define V 100
using namespace std;

typedef struct
{
 int from;
 int to;
 double flowValue;
}arrange;
 
arrange A[V*V];
 
 int structCount=0;
 int n=0;
 int e=0;
 double distance[V];
 int demandMatrix[V];
 double matrix[V][V];
 int capacity[V][V];
 int flowSent[V][V];
 int graph[V][V];
 int preD[V];
 int path[V];
 int visited[V];
 int sourceNode=1;
 int destNode=1;
 int counter=1;
 double cost=0.0;
 int sq[V];
 int dq[V];
 int sfront=-1,srear=-1;
 int dfront=-1,drear=-1;
 
 void spush(int);
 int spop();
 int sisEmpty();
 int fronts();

 void dpush(int);
 int dpop();
 int disEmpty();
 int frontd();

 int checkPath();
 void djikstras(int,int);
 void findPath(int,int);
 void sendFlow(int,int,int);
 void printResult();

 int bestcmp(const void *x, const void *y)
{
   return ( (*(arrange*)x).flowValue - (*(arrange*)y).flowValue );
}

 int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage: ./djikstras inputFileName demandFileName\n");
        exit(1);
    }

 
 //read input file
 FILE *input=fopen(argv[1],"r");
 
 char c;
 for (c = getc(input); c != EOF; c = getc(input))
        if (c == '\n') // Increment count if this character is newline
            e = e + 1;
    fclose(input);
    e=e-1;
 
 input=fopen(argv[1],"r");
 fscanf(input,"%d",&n);

 for(int i=0;i<=n;i++)
	for(int j=0;j<=n;j++)
	{
		matrix[i][j]=0;
		demandMatrix[i]=0;
		flowSent[i][j]=0;
 		graph[i][j]=0;
 	}

 for(int i=1;i<=e;i++)
 {
  double dist=0;
  int cap=0;
  int from,to=0;
  fscanf(input,"%d %d %lf %d",&from,&to,&dist,&cap);
  matrix[from][to]=dist;
  capacity[from][to]=cap;
  graph[from][to]=cap;
 }
 fclose(input);


//read demand file
FILE *demand=fopen(argv[2],"r");
e=0;
for (c = getc(demand); c != EOF; c = getc(demand))
        if (c == '\n') // Increment count if this character is newline
            e = e + 1;
    fclose(demand);
    e=e-1;

demand=fopen(argv[2],"r");
fscanf(demand,"%d",&n);
printf("%d Nodes\n",n);

 for(int i=1;i<=e;i++)
 {
  int dem=0;
  int from,to=0;
  fscanf(demand,"%d %d %d",&from,&to,&dem);
  demandMatrix[from]+=dem;
  demandMatrix[to]-=dem;
 }//end of for
 fclose(demand);


 for(int i=1;i<=n;i++)
 {
  if(demandMatrix[i]>0)
	spush(i);
  else if(demandMatrix[i]<0)
	dpush(i);	
 }

 
 int ret=0;
 while((ret=sisEmpty())!=-1)
 {
 int src=fronts();
 int dst=frontd();
 
  djikstras(src,dst);
  int rv=checkPath();

  	if(rv!=-1)
	{
  	  if(demandMatrix[src]<=abs(demandMatrix[dst]))
          {
 	  if(rv>=demandMatrix[src])
	  	sendFlow(demandMatrix[src],src,dst);
	  else
		sendFlow(rv,src,dst);
          }
          else if(demandMatrix[src]>abs(demandMatrix[dst]))
          {
           if(rv>=abs(demandMatrix[dst]))
	  	sendFlow(abs(demandMatrix[dst]),src,dst);
	   else
		sendFlow(rv,src,dst);
          }
	}
  if(demandMatrix[src]==0)
 {
	src=spop();
 }
 if(demandMatrix[dst]==0)
 {
 	dst=dpop();
 }
}
 printf("LP Variable values:\n");
 for(int i=1;i<=n;i++)
 {
  for(int j=1;j<=n;j++)
  {
   if(flowSent[i][j]>0)
   {
	printf("x%02d%02d = %d\n",i,j,flowSent[i][j]); 
   }
   if(graph[i][j]!=0)
   {
	A[structCount].from=i;
	A[structCount].to=j;
	A[structCount].flowValue=flowSent[i][j];
	structCount++;
   }
  }
 }

printf("\nMinimum Cost : %lf\n",cost);
printResult();
//printf("\nShortest Path from Node %d to Node %d is: %lf \n",sourceNode,destNode,distance[destNode]);	
}//End of main()
 
void printResult()
{
 qsort(A,structCount,sizeof(arrange),bestcmp);
 printf("\nFrom\t To\t TotalFlow\n");
 for(int i=0;i<structCount;i++)
	printf("%d\t %d\t %lf\n",A[i].from,A[i].to,A[i].flowValue);
}

void djikstras(int snode,int dnode)
{ 
    for(int k=1;k<=n;k++)
    {
        visited[k]=0;
        distance[k]=999999;
        preD[k]=0;
        path[k]=0;
    }
	
	distance[snode]=0;           //distance of Source node from itself is 0 

	for(int k=1;k<=n;k++)
	{
	 int min=-1;
    
	 for(int i=1;i<=n;i++)
	{
	 if(!visited[i]&&((min==-1)||(distance[i]<distance[min])))
	{
	 min=i;
	}
	} //End of i loop

	visited[min]=1;

	for(int i=1;i<=n;i++)
	{
	 if(matrix[min][i])
	 {
	  if(distance[min]+matrix[min][i]<distance[i])
	  {
	   distance[i]=distance[min]+matrix[min][i];
           preD[i]=min;
	  }
	 }
	}//End of x loop
	}//End of i loop

findPath(snode,dnode);
}

void findPath(int snode,int dest)
{
 counter=1;
 int tempCounter=1;
 int temp[V];
 while(preD[dest]!=0)
 {
  temp[counter]=dest;
  counter++;
  dest=preD[dest];
 }
 temp[counter]=snode;

 for(int i=counter;i>=1;i--)
	path[tempCounter++]=temp[i];

/*printf("Path Taken: \n");
 for(int i=1;i<=counter;i++)
	printf("%d \n",path[i]);*/
}

int checkPath()
{
  

 int minFlow=99999;
 for(int i=1;i<counter;i++)
 {
  //printf("Capacity[%d][%d]=%d \n",path[i],path[i+1],capacity[path[i]][path[i+1]]);
  if(capacity[path[i]][path[i+1]]!=0)
  {
	if(capacity[path[i]][path[i+1]]<=minFlow)
		minFlow=capacity[path[i]][path[i+1]];
  }
  else
  {
        //printf("failed here %d",i);
     	return -1;
  }
 }
 return minFlow;
}

void sendFlow(int flow,int from,int to)
{
 for(int i=1;i<counter;i++)
 {
  //printf("Src:%d Dst:%d Flow:%d\n",from,to,flow);
  capacity[path[i]][path[i+1]]-=flow;
  flowSent[path[i]][path[i+1]]+=flow;
  cost=cost+flow*matrix[path[i]][path[i+1]];
  if(capacity[path[i]][path[i+1]]==0)
	matrix[path[i]][path[i+1]]=0;
 }
 demandMatrix[from]-=flow;
 demandMatrix[to]+=flow;
}

void spush(int item)
{
 if(srear==V-1)
	printf("Queue Overflow \n");
 else
 {
  if(sfront==-1)
	sfront=0;
  srear=srear+1;
  sq[srear]=item;
 }
} 

void dpush(int item)
{
 if(drear==V-1)
	printf("Queue Overflow \n");
 else
 {
  if(dfront==-1)
	dfront=0;
  drear=drear+1;
  dq[drear]=item;
 }
} 

int spop()
{
 int item=-1;
 if(sfront==-1||sfront>srear)
 {
  printf("Queue Underflow \n");
 }
 else
 {
  item=sq[sfront];
  sfront=sfront+1;
 }
 return item;
}

int dpop()
{
 int item=-1;
 if(dfront==-1||dfront>drear)
 {
  printf("Queue Underflow \n");
 }
 else
 {
  item=dq[dfront];
  dfront=dfront+1;
 }
 return item;
}

int sisEmpty()
{
 if(sfront==-1||sfront>srear)
 {
  return -1;
 }
 return 1;
} 
 
int disEmpty()
{
 if(dfront==-1||dfront>drear)
 {
  return -1;
 }
 return 1;
} 

int fronts()
{
 int item=-1;
 if(sfront==-1||sfront>srear)
 {
  printf("Queue Underflow \n");
 }
 else
 {
  item=sq[sfront];
 }
 return item;
}

int frontd()
{
 int item=-1;
 if(dfront==-1||dfront>drear)
 {
  printf("Queue Underflow \n");
 }
 else
 {
  item=dq[dfront];
 }
 return item;
}
