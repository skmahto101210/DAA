#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}Node;

typedef struct List
{
	Node* head;
}List;

Node * createNode(int val)
{
	Node* new=(Node*)malloc(sizeof(Node));
	new->data=val;
	new->next=NULL;
	return new;
}

void addList(List** adjList,int u,int v)
{
	Node* new1,*new2,*temp;
	new1=createNode(v);
	new2=createNode(u);
	
	if(!adjList[u]->head)
		adjList[u]->head=new1;
	else
	{
		temp=adjList[u]->head;
		while(temp->next)
			temp=temp->next;
		temp->next=new1;
	}
	if(!adjList[v]->head)
		adjList[v]->head=new2;
	else
	{
		temp=adjList[v]->head;
		while(temp->next)
			temp=temp->next;
		temp->next=new2;
	}
}


void arti_point(List** adjList,int *visited,int *disc,int *low,int *timer,int parent,int s_node,int *ans)
{
	visited[s_node]=1;
	disc[s_node]=low[s_node]=(*timer)++;
	int child=0;
	Node*temp=adjList[s_node]->head;
	while(temp)
	{
		if(parent==temp->data)
		{
			temp=temp->next;
			continue;
		}
		else if(!visited[temp->data])
		{
			arti_point(adjList,visited,disc,low,timer,s_node,temp->data,ans);
			low[s_node] = low[s_node]<low[temp->data]?low[s_node]:low[temp->data];
			
			if(low[temp->data]>=disc[s_node] && parent!=-1)
			{
				ans[s_node]=1;
				child++;
			}
		}
		else
			low[s_node]=low[s_node]<disc[temp->data]?low[s_node]:disc[temp->data];
		temp = temp->next;
	}
	if(parent == -1 && child > 1)
		ans[s_node]=1;
}

int main()
{
	FILE* fptr=fopen("file_input2.txt","r");
	int n,e;
	fscanf(fptr,"%d",&n);
	fscanf(fptr,"%d",&e);
	
	List ** adjList=(List**)malloc(n*sizeof(List*));
	for(int i=0;i<n;i++)
	{
		adjList[i]=(List*)malloc(sizeof(List));
		adjList[i]->head=NULL;
	}
	
	while(!feof(fptr))
	{
		int u,v;
		fscanf(fptr,"%d",&u);
		fscanf(fptr,"%d",&v);
		addList(adjList,u,v);
	}
	fclose(fptr);
	
	int *visited =(int *)calloc(n,sizeof(int));
	int *disc =(int *)calloc(n,sizeof(int));
	int *low =(int *)calloc(n,sizeof(int));
	int *ans =(int *)calloc(n,sizeof(int));
	int parent=-1;
	int timer=0;
	
	for(int i=0;i<n;i++)
	{
		disc[i]=-1;
		low[i]=-1;
	}	
	
	for(int i=0;i<n;i++)
	{
		if(!visited[i])
			 arti_point(adjList,visited,disc,low,&timer,parent,i,ans);
	}
	fptr=fopen("output_arti_point.txt","wa");
	
	fputs("Articulation_Point\n",fptr);
	for(int i=0;i<n;i++)
	{
		if(ans[i]==1)
			fprintf(fptr,"%d ",i);
	}
	
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
	free(visited);

	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
