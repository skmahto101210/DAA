#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

long long int min(long long a,long long b)
{
	return a<b?a:b;
}

//long long int solve(int **A,int i,int j,int **dp)
//{
//	if(i==j) return 0;
//	
//	if(dp[i][j]!=-1) return dp[i][j];	
//	
//	long long int ans=INT_MAX;
//	for(int k=i;k<j;k++)
//	{
//		ans=min(ans,solve(A,i,k) + solve(A,k+1,j) + A[i][0]*A[k][1]*A[j][1]);
//	}
//	return dp[i][j] = ans;
//}	 
long long int solveTab(int **A,int n)
{
	int **dp = (int**)calloc(n,sizeof(int*));
	for(int i=0;i<n;i++)
		dp[i]=(int *)calloc(n,sizeof(int));
	
	for(int i=n-1; i>=0; i--)
	{
		for(int j = i+1; j < n; j++)
		{
			long long int ans=INT_MAX;
			for(int k = i; k < j; k++)
				ans=min(ans,dp[i][k] + dp[k+1][j] + A[i][0]*A[k][1]*A[j][1]);
			dp[i][j] = ans;		
		}		
	}
	
	return dp[0][n-1];
}	
int main()
{
	FILE* fptr=fopen("matrices_inputs.txt","r");
	
	int n,i=0;
	fscanf(fptr,"%d",&n);
	
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

	fptr=fopen("min_multi_matrices_output.txt","wa");
	//fprintf(fptr,"Min Multiplication of Matrices:- %lld",solve(A,0,n-1,dp));
	fprintf(fptr,"Min Multiplication of Matrices:- %lld",solveTab(A,n));
	fclose(fptr);

	return 0;
}
