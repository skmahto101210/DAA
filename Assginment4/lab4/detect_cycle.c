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


int isCycle(List** adjList,int *visited,int parent,int s_node)
{
	visited[s_node]=1;
	Node*temp=adjList[s_node]->head;
	while(temp)
	{
		if(!visited[temp->data])
		{
			int ans = isCycle(adjList,visited,s_node,temp->data);
			if(ans == 1) return 1;
		}
		else if(parent != temp->data)
			return 1;
		temp = temp->next;
	}
	return 0;
}


int main()
{
	FILE* fptr=fopen("file_input1.txt","r");
	int n,e;
	fscanf(fptr,"%d",&n);
	fflush(stdin);
	fscanf(fptr,"%d",&e);
	fflush(stdin);
	
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
		fflush(stdin);
		fscanf(fptr,"%d",&v);
		fflush(stdin);
		addList(adjList,u,v);
	}
	fclose(fptr);
	
	int *visited =(int *)calloc(n,sizeof(int));
	int parent=-1;
	int ans = 0;
	
	for(int i=0;i<n;i++)
	{
		if(!visited[i])
			ans = isCycle(adjList,visited,parent,i);
		if(ans) break;
	}
	fptr=fopen("output_cycle.txt","wa");
	
	if(ans==1)
		fputs("Yes,Cycle is present",fptr);
	else
		fputs("No,Cycle is not present",fptr);
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
