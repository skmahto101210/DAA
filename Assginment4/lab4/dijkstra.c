#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int data;
	int wt;
	struct node* next;
}Node;

typedef struct List
{
	Node* head;
}List;

Node * createNode(int val,int wt)
{
	Node* new=(Node*)malloc(sizeof(Node));
	new->data=val;
	new->wt = wt;
	new->next=NULL;
	return new;
}

void addList(List** adjList,int u,int v,int wt)
{
	Node* new1,*temp;
	new1=createNode(v,wt);
	
	if(!adjList[u]->head)
		adjList[u]->head=new1;
	else
	{
		temp=adjList[u]->head;
		while(temp->next)
			temp=temp->next;
		temp->next=new1;
	}
}

int findmin(int **pri_que,int n)
{
	int min;
	for(int i=0;i<n;i++)
	{
		if(pri_que[i][2]==0)
		{	
			min=i;
			break;
		}	
	}		
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(pri_que[min][1]>pri_que[j][1]&&pri_que[j][2]==0)
				min=j;
		}
	}
	pri_que[min][2]=1;
	return pri_que[min][0];		
}
int main()
{
	FILE* fptr=fopen("file_input4.txt","r");
	int n,e,sour;
	fscanf(fptr,"%d",&n);
	fscanf(fptr,"%d",&e);
	fscanf(fptr,"%d",&sour);
	
	List ** adjList=(List**)malloc(n*sizeof(List*));
	for(int i=0;i<n;i++)
	{
		adjList[i]=(List*)malloc(sizeof(List));
		adjList[i]->head=NULL;
	}
	
	while(!feof(fptr))
	{
		int u,v,wt;
		fscanf(fptr,"%d",&u);
		fscanf(fptr,"%d",&v);
		fscanf(fptr,"%d",&wt);
		addList(adjList,u,v,wt);
	}
	fclose(fptr);
	
	
	int *dist =(int *)calloc(n,sizeof(int));
	for(int i=0;i<n;i++)
		dist[i]=1e9;
	dist[0]=0;
	
	int **pri_que = (int **)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
	{
		pri_que[i]=(int*)malloc(3*sizeof(int));
		Node*temp = adjList[i]->head;
		while(temp)
		{
			pri_que[temp->data][0] = i;
			pri_que[temp->data][1] = temp->wt;
			pri_que[temp->data][2] = 0;
		}
	}
	
	int end=0;
	while(end!=n)
	{
		int u = findmin(pri_que,n);
		end++;
		Node*temp=adjList[u]->head;
		while(temp)
		{
			if(dist[u]!=1e9 && dist[u] + temp->wt<dist[temp->data])
				dist[temp->data]=dist[u]+temp->wt;
		}
	}
	
	

	fptr=fopen("output_dijkstra.txt","wa");

	fprintf(fptr,"Sour to Dest -> Cost\n");
	for(int i=0;i<n;i++)
		fprintf(fptr,"  %d  to  %d   ->  %d\n",sour,i,dist[i]);

	fclose(fptr);
	for(int i=0;i<n;i++)
	{
		Node*temp=adjList[i]->head;
		while(temp)
		{
			Node*next=temp->next;
			free(temp);
			temp=next;
		}
		free(adjList[i]);
	}
	free(adjList);
	free(dist);

	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
