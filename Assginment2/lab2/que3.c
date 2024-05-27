#include<stdio.h>
#include<stdlib.h>

void add(int n,int a[n][n],int b[n][n],int c[n][n])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			c[i][j]=a[i][j]+b[i][j];	
	}
}
void sub(int n,int a[n][n],int b[n][n],int c[n][n])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			c[i][j]=a[i][j]-b[i][j];	
	}
}



void sa(int n,int a[n][n],int b[n][n],int c[n][n])
{
	if(n==1)
	{
		c[0][0]=a[0][0]*b[0][0];
	}
	else
	{
		int new_size=n/2;
		int a11[new_size][new_size],a12[new_size][new_size],a21[new_size][new_size],a22[new_size][new_size],b11[new_size][new_size],b12[new_size][new_size],b21[new_size][new_size],b22[new_size][new_size],c11[new_size][new_size],c12[new_size][new_size],c21[new_size][new_size],c22[new_size][new_size],p[new_size][new_size],q[new_size][new_size],r[new_size][new_size],s[new_size][new_size],t[new_size][new_size],u[new_size][new_size],v[new_size][new_size],aResult[new_size][new_size],bResult[new_size][new_size];	
		
		for(int i=0;i<new_size;i++)
		{
			for(int j=0;j<new_size;j++)
			{
				a11[i][j]=a[i][j];
				a12[i][j]=a[i][j+new_size];
				a21[i][j]=a[i+new_size][j];
				a22[i][j]=a[i+new_size][j+new_size];
				
				b11[i][j]=b[i][j];
				b12[i][j]=b[i][j+new_size];
				b21[i][j]=b[i+new_size][j];
				b22[i][j]=b[i+new_size][j+new_size];
			}		
		}
		
		add(new_size,a11,a22,aResult);
		add(new_size,b11,b22,bResult);
		sa(new_size,aResult,bResult,p);
		
		add(new_size,a21,a22,aResult);
		sa(new_size,aResult,b11,q);
		
		sub(new_size,b12,b22,bResult);
		sa(new_size,a11,bResult,r);
		
		sub(new_size,b21,b11,bResult);
		sa(new_size,a22,bResult,s);
		
		add(new_size,a11,a12,aResult);
		sa(new_size,aResult,b22,t);
		
		sub(new_size,a21,a11,aResult);
		add(new_size,b11,b12,bResult);
		sa(new_size,aResult,bResult,u);
		
		sub(new_size,a12,a22,aResult);
		add(new_size,b21,b22,bResult);
		sa(new_size,aResult,bResult,v);
		
		add(new_size,p,s,c11);
		add(new_size,c11,v,c11);
		sub(new_size,c11,t,c11);
		
		add(new_size,r,t,c12);
		add(new_size,q,s,c21);
		
		add(new_size,p,r,c22);
		add(new_size,c22,u,c22);
		sub(new_size,c22,q,c22);
		
		for(int i=0;i<new_size;i++)
		{
			for(int j=0;j<new_size;j++)
			{
				c[i][j]=c11[i][j];
				c[i][j+new_size]=c12[i][j];
				c[i+new_size][j]=c21[i][j];
				c[i+new_size][j+new_size]=c22[i][j];
			}		
		}
	}
}

int main()
{
	FILE*fptr=fopen("file_input3.txt","r");
	int n,temp;
	while(!feof(fptr))
	{
		if(fscanf(fptr,"%d",&temp)==1)
		{
			n=temp;
			break;		
		}
	}
	int mat1[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			while(!feof(fptr))
			{
				if(fscanf(fptr,"%d",&temp)==1)
				{
					mat1[i][j]=temp;
					break;
				}
			}	
		}	
	}	
	while(!feof(fptr))
	{
		if(fscanf(fptr,"%d",&temp)==1)
		{
			n=temp;
			break;		
		}
	}
	int mat2[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			while(!feof(fptr))
			{
				if(fscanf(fptr,"%d",&temp)==1)
				{
					mat2[i][j]=temp;
					break;
				}
			}	
		}	
	}	
	fclose(fptr);
	
	fptr=fopen("outpur_file3.txt","wa");
	int result[n][n];
	sa(n,mat1,mat2,result);	
	fputs("Result_matrix:-\n\t",fptr);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			fprintf(fptr,"%d ",result[i][j]);
		fputs("\n\t",fptr);	
	}
	fclose(fptr);
		
	return 0;
}
