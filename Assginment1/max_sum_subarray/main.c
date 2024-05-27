#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
	if (a < b)
		return b;
	return a;
}

int maxSumSubarray(int *arr, int n)
{
	int sum = 0;
	int maxi = -1331233;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
		maxi = max(maxi, sum);
		if (sum < 0)
			sum = 0;
	}
	if (n == 0)
		return -47982371;
	return maxi;
}

int main()
{
	int *arr = (int *)calloc(1000, sizeof(int));
	int size = 0;
	FILE *fptr;
	fptr = fopen("file_input.txt", "r");
	while (!feof(fptr))
	{
		int val;
		if (fscanf(fptr, "%d", &val) == 1)
		{
			arr[size] = val;
			size++;
		}
	}
	fclose(fptr);
	fptr = fopen("max_sum_output.txt", "wa");
	fprintf(fptr, "Max Sum :- %d", maxSumSubarray(arr, size));
	printf("Max_Sum_Subarray:- %d\n", maxSumSubarray(arr, size));

	return 0;
}
