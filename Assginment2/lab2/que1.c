#include<stdio.h>
#include<stdlib.h>


int find_peak(int *arr,int size)
{
	int low=0;
	int high=size-1;
	while(low<high)
	{
		int mid=low+(high-low)/2;
		if(arr[mid-1]<arr[mid]&&arr[mid]>arr[mid+1])
			return mid;
			
		if(arr[mid-1]>arr[mid]&&arr[mid]>arr[mid+1])
			high = mid-1;
		
		if(arr[mid-1]<arr[mid]&&arr[mid]<arr[mid+1])
			low = mid;
	}
}

int main()
{
	int *arr=(int *)calloc(1000,sizeof(int));
	FILE* fptr;
	fptr = fopen("file_input1.txt","r");
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
	fptr=fopen("output_file1.txt","wa");
	for(int i=0;i<size;i++)
		fprintf(fptr,"%d ",arr[i]);
	fputs("\nPeak of the array is:- ",fptr);
	int peak_index=find_peak(arr,size);
	fprintf(fptr,"%d",arr[peak_index]);
	


	return 0;
}
