#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#define V 100
using namespace std;

int n=0,e=0;
int graph[V][V];
double cost[V][V];
int imbalance[V];
int adjacency[V][V];

int main(int argc,char *argv[])
{
 if(argc!=3)
 {
  printf("Usage: ./3 inputFileName.txt demandFileName.txt \n");
  exit(0);
 }

 char *inputFile=argv[1];
 char *demandFile=argv[2];
 int from=2;
 int to=3;
 
 for(from=0;from<=V;from++)
	for(to=0;to<=V;to++)
		adjacency[from][to]=0;

from=0;
to=0;

 char c;
 FILE *input=fopen(inputFile,"r");
    
    for (c = getc(input); c != EOF; c = getc(input))
        if (c == '\n') // Increment count if this character is newline
            e = e + 1;
    fclose(input);

    e=e-1;
    input=fopen(inputFile,"r");
    fscanf(input,"%d",&n);

char of[2000000]="";
	 
int capacity=0;
double price=0.0;
FILE *output=fopen("output.lp","w+");

fprintf(output,"%s","Minimize\n");
fprintf(output,"%s"," obj: ");
   
for(int edge=1;edge<=e;edge++)
{
 char costinstr[10]="";
 char variableName[5]="";
 fscanf(input,"%d %d %lf %d",&from,&to,&price,&capacity);;
 sprintf(costinstr, "%.2lf ", price);
 strcat(of,costinstr);
 sprintf(variableName, "x%02d%02d",from,to);
 strcat(of,variableName);
 if(edge!=e)
 	strcat(of," + ");
 graph[from][to]=capacity;
 adjacency[from][to]=1;
 cost[from][to]=price;
}
fprintf(output,"%s",of);
fprintf(output,"%s","\n\nSubject To\n");
fclose(input);
 
e=0;

FILE *demand=fopen(demandFile,"r");
for (c = getc(demand); c != EOF; c = getc(demand))
        if (c == '\n') // Increment count if this character is newline
            e = e + 1;
    fclose(demand);

    e=e-1;
    n=0;
    demand=fopen(demandFile,"r");
    fscanf(demand,"%d",&n);

int dem=0;
for(int i=0;i<=V;i++)
	imbalance[i]=0;

for(int edge=1;edge<=e;edge++)
{
 dem=0;
 fscanf(input,"%d %d %d",&from,&to,&dem);
 imbalance[from]+=dem;
 imbalance[to]-=dem;
}


int counter=1;
int first=1;
for(int i=1;i<=n;i++)
{
  char cons_p[2000000]="";
  char cons_n[2000000]="";
  char cn[10]="";

  sprintf(cn, " c%d: ",counter);
  fprintf(output,"%s",cn);
  
 first=1;
 for(int j=1;j<=n;j++)
 {
  char node[6]="";
  if(adjacency[i][j]==1&&first==1)
  {
  sprintf(node, "x%02d%02d",i,j);
  strcat(cons_p,node);
  first=2;
  }
  else if(adjacency[i][j]==1&&first!=1)
  {
  strcat(cons_p," + ");
  sprintf(node, "x%02d%02d",i,j);
  strcat(cons_p,node);
  }
  printf("");
  if(adjacency[j][i]==1)
  {
   strcat(cons_n," - ");
   sprintf(node, "x%02d%02d",j,i);
   strcat(cons_n,node);
  }
  
 }
 //printf("%s\n",cons_p);
 fprintf(output,"%s",cons_p);
 //printf("%s\n",cons_n);
 fprintf(output,"%s",cons_n);
 fprintf(output," = %d",imbalance[counter]);
 fprintf(output,"%s","\n");
 counter++;
}

fprintf(output,"%s","\n");
fprintf(output,"%s","Bounds\n");


for(int i=1;i<=n;i++)
{
  for(int j=1;j<=n;j++)
  {
        if(adjacency[i][j]==1)
	{
        char cn[10]="";
        sprintf(cn,"x%02d%02d",i,j);
        fprintf(output," 0 <= %s <= %d\n",cn,graph[i][j]);
	//printf("%d: %d\n",i,imbalance[i]);
        }
  }
}
fprintf(output,"\n%s","End");
fclose(output);
printf("An output file named output.lp has been created. Load and execute this file in cplex \n");
}
