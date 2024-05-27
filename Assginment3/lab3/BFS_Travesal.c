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
	Node*new1,*new2,*temp;
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

void bfs(List**adjList,int *visited,int *ans,int s_node,int n,int *ans_index)
{
	int *queue=(int*)malloc(n*sizeof(int));
	int f=-1,r=-1;
	queue[++r]=s_node;
	visited[s_node]=1;
	while(f<r)
	{
		int frontNode=queue[++f];
		ans[(*ans_index)++]=frontNode;
		Node*temp=adjList[frontNode]->head;
		while(temp)
		{
			if(!visited[temp->data])
			{
				queue[++r]=temp->data;
				visited[temp->data]=1;
			}
			temp=temp->next;
		}
	}
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
	int *ans=(int *)calloc(n,sizeof(int));
	int ans_index=0;
	for(int i=0;i<n;i++)
	{
		if(!visited[i])
			bfs(adjList,visited,ans,i,n,&ans_index);
	}
	
	fptr=fopen("BFS_output.txt","wa");
	fputs("BFS_Traversal:-",fptr);
	for(int i=0;i<n;i++)
	{
		fprintf(fptr,"%d ",ans[i]);
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
	free(ans);
		
	return 0;
}

