#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node*next;
}Node;

typedef struct List
{
	Node*head;
}List;

Node* createNode(int val)
{
	Node* new=(Node*)malloc(sizeof(Node));
	new->data=val;
	new->next=NULL;
	return new;
}

void addList(List **adjList,int u,int v)
{
	Node*new, *temp;
	new=createNode(v);
	if(!adjList[u]->head)
		adjList[u]->head=new;
	else
	{
		temp=adjList[u]->head;
		while(temp->next)
			temp=temp->next;
		temp->next=new;
	}
}

int isCycle_present(List**adjList,int *visited,int *dfs_visited,int s_node)
{
	visited[s_node]=1;
	dfs_visited[s_node]=1;
	Node*temp=adjList[s_node]->head;
	while(temp)
	{	
		if(!visited[temp->data])
		{
			int ans = isCycle_present(adjList,visited,dfs_visited,temp->data);
			if(ans==1)return 1;
		}
		else if(dfs_visited[temp->data])
			return 1;
		temp=temp->next;
	}
	return 0;
}

void dfs(List**adjList,int *visited,int *stack,int s_node,int *top)
{
	visited[s_node]=1;
	Node*temp=adjList[s_node]->head;
	while(temp)
	{	
		if(!visited[temp->data])
			dfs(adjList,visited,stack,temp->data,top);
		temp=temp->next;
	}
	stack[++(*top)]=s_node;
}

int main()
{
	FILE* fptr=fopen("file_input1.txt","r");
	int n,e;
	fscanf(fptr,"%d",&n);
	fscanf(fptr,"%d",&e);
	
	List** adjList=(List**)malloc(n*sizeof(List*));
	for(int i=0;i<n;i++)
	{
		adjList[i]=(List*)malloc(sizeof(List));
		adjList[i]->head=NULL;
	}
	
	for(int i=0;i<e;i++)
	{
		int u,v;
		fscanf(fptr,"%d",&u);
		fscanf(fptr,"%d",&v);
		addList(adjList,u,v);
	}
	fclose(fptr);
	
	int *visited=(int *)calloc(n,sizeof(int));
	int *stack=(int *)calloc(n,sizeof(int));
	int top=-1;
	
	for(int i=0;i<n;i++)
	{
		if(!visited[i])
			dfs(adjList,visited,stack,i,&top);
	}
	
	fptr=fopen("Topology_sort_output.txt","wa");
	fputs("Topology Sort:-",fptr);
	while(top!=-1)
	{
		fprintf(fptr,"%d ",stack[top--]);
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
	free(stack);
		
	return 0;
}

