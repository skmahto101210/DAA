#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

int max(int a,int b)
{
	return a<b?b:a;
}

int solve(char *str1,char *str2,int n,int m,int *seq)
{
	int **mat = (int**)calloc(n+1,sizeof(int*));
	for(int i=0;i<n+1;i++)
		mat[i]=(int *)calloc(n+1,sizeof(int));
	
	for(int i=1;i<n+1;i++)
	{
		for(int j=1;j<m+1;j++)
		{
			if(str1[i-1]==str2[j-1])
				mat[i][j] = mat[i-1][j-1] + 1;
			else
				mat[i][j] = max(mat[i-1][j], mat[i][j-1]);
		}
	}
	
	int i=n,j=m;
	while(i>0&&j>0)
	{
		if(str1[i-1]==str2[j-1])
		{
			seq[i-1] = 1;
			i--;j--;
		}
		else if(mat[i-1][j]>mat[i][j-1])
			i--;
		else
			j--;
	}
	return mat[n][m];
}	
	
int main()
{
	FILE* fptr=fopen("Two_sequence_inputs.txt","r");
	
	int n,m;
	fscanf(fptr,"%d",&n);
	fscanf(fptr,"%d",&m);
	
	char *str1=(char*)malloc(n+1*sizeof(char));
	char *str2=(char*)malloc(m+1*sizeof(char));
	int *seq = (int*)calloc(n,sizeof(int));
	
    	fscanf(fptr,"%s",str1);
    	fscanf(fptr,"%s",str2);
	fclose(fptr);
	
	fptr=fopen("Long_common_sub_output.txt","wa");
	fprintf(fptr,"Size of Longest Common SubSequence:- %d\nSubSequence:- ",solve(str1,str2,n,m,seq));
	for(int i=0;i<n;i++)
	{
		if(seq[i] == 1)
			fprintf(fptr,"%c",str1[i]);
	}
	
	fclose(fptr);

	return 0;
}
