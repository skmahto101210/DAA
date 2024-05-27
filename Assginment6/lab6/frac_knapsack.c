#include<stdio.h>
#include<stdlib.h>

void swap(float* a,float*b)
{
	float temp = a[0];
	a[0] = b[0];
	b[0] = temp;
	temp = a[1];
	a[1] = b[1];
	b[1] = temp;
}
		
int quick_sort(float **frac,int low,int high)
{
	int pivotIndex = low + rand()%(high - low +1);
	swap(frac[pivotIndex],frac[high]);
	float *pivot = frac[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (pivot[0] < frac[j][0])
		{
			i++;
			swap(frac[i], frac[j]);
		}
	}
	swap(frac[i + 1], frac[high]);
	return i + 1;
}

void sort_frac(float** frac,int n,int low,int high)
{
	if(low<=high)
	{
		int parti = quick_sort(frac,low,high);
		sort_frac(frac,n,low,parti-1);
		sort_frac(frac,n,parti+1,high);
	}
}
		
int main()
{
	FILE* fptr=fopen("frac_knapsack_inputs.txt","r");
	
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

	float **frac = (float **)malloc(n*sizeof(float*));
	for(int i=0;i<n;i++)
		frac[i] = (float *)malloc(2*sizeof(float));
		
	for(int i=0;i<n;i++)
	{
		frac[i][0] = (float)A[i][0]/A[i][1];
		frac[i][1] = i;
	}
	
	sort_frac(frac,n,0,n-1);
	fptr=fopen("frac_knapsack_output.txt","wa");
	fprintf(fptr,"Max Values:- ");
	for(int  i=0;i<n;i++)
	{
		if(wt==0) break;
		if(wt >= A[(int)frac[i][1]][1])
		{
			fprintf(fptr,"%d ",A[(int)frac[i][1]][0]);
			wt -= A[(int)frac[i][1]][1];
		}
		else
		{
			fprintf(fptr,"%0.3f ",(float)A[(int)frac[i][1]][0]/((float)A[(int)frac[i][1]][1]/wt));
			wt == 0;
			break;
		}
	}
	
	return 0;
}
