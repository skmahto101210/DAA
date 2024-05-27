#include<stdio.h>
#include<stdlib.h>

void sort(int *arr,int low,int high)
{
	for(int i=low,i<high+1;i++)
	{
		int key=arr[low];
		int j=i;
		while(j>=0&&arr[j]>key)
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
}


int deter_select(int *arr,int low,int high,int k)
{
	if(high-low<=5)
		sort(arr,low,high);
	
	sort(arr,low,high,k);
	deter_select(arr,low+5,high,k);



}


int main()
{
	FILE* fptr;
	fptr =fopen("file_input3.txt","r");
	int *arr=(int *)calloc(1000,sizeof(int));
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
	
	deter_select(arr,0,size-1);



	return 0;
}
