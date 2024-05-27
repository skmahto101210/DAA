#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Bubble_sort(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
				swap(arr + j, arr + j + 1);
		}
	}
}

void Insertion_sort(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && key < arr[j])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void Msort(int *arr, int low, int mid, int high)
{
	int i = low;
	int j = mid + 1;
	int k = 0;
	int *tarr = (int *)malloc((high - low + 1) * sizeof(int));
	while (i <= mid && j <= high)
	{
		if (arr[i] >= arr[j])
			tarr[k++] = arr[j++];
		else
			tarr[k++] = arr[i++];
	}
	while (i <= mid)
		tarr[k++] = arr[i++];
	while (j <= high)
		tarr[k++] = arr[j++];

	for (i = low; i <= high; i++)
		arr[i] = tarr[i - low];
	free(tarr);
}

void Merge_sort(int *arr, int low, int high)
{
	if (low < high)
	{
		int partition = low + (high - low) / 2;
		Merge_sort(arr, low, partition);
		Merge_sort(arr, partition + 1, high);
		Msort(arr, low, partition, high);
	}
}

void three_way_Msort(int *arr, int low, int mid1, int mid2, int high)
{
	int i = low;
	int j = mid1 + 1;
	int l = mid2 + 1;
	int k = 0;
	int *tarr = (int *)malloc((high - low + 1) * sizeof(int));
	while (i <= mid1 && j <= mid2 && l <= high)
	{
		if (arr[i] <= arr[j] && arr[i] <= arr[l])
			tarr[k++] = arr[i++];
		else if (arr[j] <= arr[i] && arr[j] <= arr[l])
			tarr[k++] = arr[j++];
		else
			tarr[k++] = arr[l++];
	}
	while (i <= mid1 && j <= mid2)
	{
		if (arr[i] <= arr[j])
			tarr[k++] = arr[i++];
		else
			tarr[k++] = arr[j++];
	}
	while (j <= mid1 && l <= high)
	{
		if (arr[j] <= arr[l])
			tarr[k++] = arr[j++];
		else
			tarr[k++] = arr[l++];
	}
	while (i <= mid1 && l <= high)
	{
		if (arr[i] <= arr[l])
			tarr[k++] = arr[i++];
		else
			tarr[k++] = arr[l++];
	}
	while (i <= mid1)
		tarr[k++] = arr[i++];
	while (j <= mid2)
		tarr[k++] = arr[j++];
	while (l <= high)
		tarr[k++] = arr[l++];

	for (i = low; i <= high; i++)
		arr[i] = tarr[i - low];
	free(tarr);
}

void three_way_merge_sort(int *arr, int low, int high)
{
	if (low < high)
	{
		int mid1 = low + (high - low) / 3;
		int mid2 = low + 2 * (high - low) / 3;
		three_way_merge_sort(arr, low, mid1);
		three_way_merge_sort(arr, mid1 + 1, mid2);
		three_way_merge_sort(arr, mid2 + 1, high);
		three_way_Msort(arr, low, mid1, mid2, high);
	}
}

int Qsort_first(int *arr, int low, int high)
{
	int pivot = arr[low];
	int i = high + 1;
	for (int j = high; j > low; j--)
	{
		if (pivot < arr[j])
		{
			i--;
			swap(arr + i, arr + j);
		}
	}
	swap(arr + i - 1, arr + low);
	return i - 1;
}

void quickSort_first(int *arr, int low, int high)
{
	if (low <= high)
	{
		int partition = Qsort_first(arr, low, high);
		quickSort_first(arr, low, partition - 1);
		quickSort_first(arr, partition + 1, high);
	}
}

int Qsort_last(int *arr, int low, int high)
{
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (pivot > arr[j])
		{
			i++;
			swap(arr + i, arr + j);
		}
	}
	swap(arr + i + 1, arr + high);
	return i + 1;
}

void quickSort_last(int *arr, int low, int high)
{
	if (low <= high)
	{
		int partition = Qsort_last(arr, low, high);
		quickSort_last(arr, low, partition - 1);
		quickSort_last(arr, partition + 1, high);
	}
}

int Qsort_random(int *arr, int low, int high)
{
	int piviotIndex = low + rand() % (high - low + 1);
	swap(arr + piviotIndex, arr + high);
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (pivot > arr[j])
		{
			i++;
			swap(arr + i, arr + j);
		}
	}
	swap(arr + i + 1, arr + high);
	return i + 1;
}

void quickSort_random(int *arr, int low, int high)
{
	if (low <= high)
	{
		int partision = Qsort_random(arr, low, high);
		quickSort_random(arr, low, partision - 1);
		quickSort_random(arr, partision + 1, high);
	}
}

void count_sort(int *arr, int size)
{
	int max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}

	int *temp = (int *)calloc(max + 1, sizeof(int));
	for (int i = 0; i < size; i++)
		temp[arr[i]]++;

	for (int i = 0, j = 0; i <= max;)
	{
		if (temp[i])
		{
			arr[j] = i;
			j++;
			temp[i]--;
		}
		else
			i++;
	}
}

void heapfy(int *arr, int size, int index)
{
	int largest = index;
	int left = 2 * largest + 1;
	int right = 2 * largest + 2;

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

void build_heap(int *arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		heapfy(arr, size, i);
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
	int *arr = (int *)malloc(1000 * sizeof(int));
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

	fptr = fopen("sort_output.txt", "wa");

	int choose = 0;
	while (choose != 10)
	{
		printf("\nOperation:- \n"
			   "\t1.Bubble Sort\n"
			   "\t2.Insretion Sort\n"
			   "\t3.Merge Sort\n"
			   "\t4.3-way Merge Sort\n"
			   "\t5.Quick_sort_first_as_pivot\n"
			   "\t6.Quick_sort_last_as_pivot\n"
			   "\t7.Quick_sort_random_as_pivot\n"
			   "\t8.Coun_sort\n"
			   "\t9.Heap_sort\n"
			   "\t10.exit()\n"
			   "choose option:- ");
		scanf("%d", &choose);
		fflush(stdin);
		switch (choose)
		{
		case 1:
			Bubble_sort(arr, size);
			fputs("Bubble sort: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 2:
			Insertion_sort(arr, size);
			fputs("Insertion_sort: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 3:
			Merge_sort(arr, 0, size - 1);
			fputs("Merge_sort: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 4:
			three_way_merge_sort(arr, 0, size - 1);
			fputs("3-way Merge Sort: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 5:
			quickSort_first(arr, 0, size - 1);
			fputs("Quick_sort_first_as_pivot: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 6:
			quickSort_last(arr, 0, size - 1);
			fputs("Quick_sort_last_as_pivot: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 7:
			quickSort_random(arr, 0, size - 1);
			fputs("Quick_sort_random_as_pivot: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 8:
			quickSort_last(arr, 0, size - 1);
			fputs("Coun_sort: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;
		case 9:
			build_heap(arr, size);
			heapsort(arr, size);
			fputs("Heap_Sort: ", fptr);
			for (int i = 0; i < size; i++)
				fprintf(fptr, "%d ", arr[i]);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(sort(output).txt)##\n");
			break;

		case 10:
			printf("You are exit...\n");
			break;
		default:
			printf("choose right option...\n");
		}
	}
	fclose(fptr);

	return 0;
}
