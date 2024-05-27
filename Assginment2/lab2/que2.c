#include<stdio.h>
#include<stdlib.h>

long long power(int x,int y)
{
	if(y==0)return 1;
	else if(y&1) return (long)x*power(x,y/2)*power(x,y/2);
	return power(x,y/2)*power(x,y/2);
}

int main()
{
	FILE* fptr;
	fptr=fopen("file_input2.txt","r");
	int *arr=(int *)calloc(2,sizeof(int));
	int size=0;
	
	while(!feof(fptr))
	{
		int val;
		if(fscanf(fptr,"%d",&val)==1)
		{
			arr[size]=val;
			size++;
		}
	}
	fclose(fptr);
	fptr=fopen("output_file2.txt","wa");
	fprintf(fptr,"X = %d, Y = %d;\n",arr[0],arr[1]);
	fprintf(fptr,"X^Y:- %lld",power(arr[0],arr[1]));


	return 0;
}

