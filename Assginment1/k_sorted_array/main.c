#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapfy(int *arr, int size, int index)
{
	int largest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < size && arr[largest] < arr[left])
		largest = left;
	if (right < size && arr[largest] < arr[right])
		largest = right;

	if (largest != index)
	{
		swap(arr + largest, arr + index);
		heapfy(arr, size, largest);
	}
}

void insertheap(int *arr, int data, int index)
{
	arr[index] = data;
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if (parent >= 0 && arr[parent] < arr[index])
		{
			swap(arr + parent, arr + index);
			index = parent;
		}
		else
			break;
	}
}

void heapsort(int *arr, int size)
{
	for (int i = size - 1; i >= 0; i--)
	{
		swap(arr, arr + i);
		heapfy(arr, i, 0);
	}
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
			insertheap(arr, val, size);
			size++;
		}
	}
	fclose(fptr);

	heapsort(arr, size);

	fptr = fopen("K_sorted_list_output.txt", "wa");
	for (int i = 0; i < size; i++)
		fprintf(fptr, "%d ", arr[i]);
	fputs("\n", fptr);
	fclose(fptr);

	return 0;
}
