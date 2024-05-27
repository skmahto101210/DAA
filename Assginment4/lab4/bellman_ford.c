#include<stdio.h>
#include<stdlib.h>


typedef struct Edge
{
	int u;
	int v;
	int wt;
}Edge;

void bellman(Edge* edges,int *dist,int e,int sour)
{
	dist[sour]=0;
	for(int i=0;i<e;i++)
	{
		int u=edges[i].u;
		int v=edges[i].v;
		int wt=edges[i].wt;
		if(dist[u]!=1e9&&dist[u]+wt<dist[v])
			dist[v]=dist[u]+wt;
	}
}

int main()
{
	FILE* fptr=fopen("file_input3.txt","r");
	int n,e;
	fscanf(fptr,"%d",&n);
	fscanf(fptr,"%d",&e);
	
	int sour;
	fscanf(fptr,"%d",&sour);
	
	Edge *edges=(Edge*)malloc(e*sizeof(Edge));
	int i=0;
	while(!feof(fptr))
	{
		int u,v,wt;
		fscanf(fptr,"%d",&u);
		fscanf(fptr,"%d",&v);
		fscanf(fptr,"%d",&wt);
		edges[i].u = u;
		edges[i].v=v;
		edges[i].wt=wt;
		i++;		
	}
	fclose(fptr);
	
	int *dist =(int *)calloc(n,sizeof(int));
	for(int i=0;i<n;i++)
		dist[i]=1e9;

	for(int i=0;i<n-1;i++)
		bellman(edges,dist,e,sour);
	
	//for checking -ve weight cycle
	int flag=0;
	for(int i=0;i<e;i++)
	{
		int u=edges[i].u;
		int v=edges[i].v;
		int wt=edges[i].wt;
		if(dist[u]!=1e9&&dist[u]+wt<dist[v])
		{
			flag=1;
			break;
		}		
	}
	fptr=fopen("output_bellman_ford.txt","wa");
	if(flag==0)
	{
		fprintf(fptr,"Sour to Dest -> Cost\n");
		for(int i=0;i<n;i++)
			fprintf(fptr,"  %d  to  %d   ->  %d\n",sour,i,dist[i]);
	}
	else
		fputs("-ve weight cycle present in the graph",fptr);
	fclose(fptr);
	
	free(edges);
	free(dist);

	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
