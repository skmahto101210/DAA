#include<stdio.h>
#include<stdlib.h>

void solve_greedy(int **A,int n,FILE* fptr)
{
	int i=0,j=0;
	
	for(j=1;j<n;j++)
	{
		if(A[i][1]<=A[j][0])
		{
			fprintf(fptr,"(s- %d, f- %d)\n",A[i][0],A[i][1]);
			i=j;
		}
	}
}

int main()
{
	FILE* fptr=fopen("ASP_inputs.txt","r");
	
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

	fptr=fopen("ASP_output.txt","wa");
	fprintf(fptr,"Selected Values:- \n");
	solve_greedy(A,n,fptr);
	fclose(fptr);
	
	return 0;
}
