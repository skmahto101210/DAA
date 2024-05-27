#include<stdio.h>
#include<stdlib.h>

int max(int a,int b)
{
	return a<b?b:a;
}

int solve(int **A,int index,int wt,int** dp)
{
	if(index < 0) return 0;
	
	if(dp[index][wt]!=-1) return dp[index][wt];
	
	int include=0;
	if(A[index][1]<=wt)
		include = A[index][0] + solve(A,index-1,wt-A[index][1],dp);
	int exclude = solve(A,index-1,wt,dp);
	
	return dp[index][wt]=max(include,exclude);	
}	

int main()
{
	FILE* fptr=fopen("knapsack_inputs.txt","r");
	
	int n,wt,i=0;
	fscanf(fptr,"%d",&n);
	fscanf(fptr,"%d",&wt);
	
	int **A = (int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		A[i]=(int *)malloc(2*sizeof(int));
		
	while(!feof(fptr))
	{
		fscanf(fptr,"%d",A[i]+0);
		fscanf(fptr,"%d",A[i]+1);
		i++;
	}
	fclose(fptr);
	
	int **dp = (int**)calloc(n,sizeof(int*));
	for(int i=0;i<n;i++)
		dp[i] = (int *)calloc(wt+1,sizeof(int));
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<wt+1;j++)
			dp[i][j]=-1;
	}
	
	fptr=fopen("knapsack_output.txt","wa");
	fprintf(fptr,"Max Values:- %d",solve(A,n-1,wt,dp));
	fclose(fptr);

	return 0;
}
