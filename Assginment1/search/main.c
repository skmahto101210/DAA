#include <stdio.h>
#include <stdlib.h>
#define Max_size 1000

int Linera_search(int *arr, int n, int key, int *comp)
{
	for (int i = 0; i < n; i++)
	{
		*comp = i + 1;
		if (arr[i] == key)
			return 1;
	}
	return 0;
}

int Binary_search(int *arr, int key, int low, int high, int *comp)
{
	if (low <= high)
	{
		(*comp)++;
		int mid = low + (high - low) / 2;
		if (arr[mid] == key)
			return 1;
		else if (arr[mid] > key)
			return Binary_search(arr, key, low, mid - 1, comp);
		else
			return Binary_search(arr, key, mid + 1, high, comp);
	}
	return 0;
}

int Ternary_search(int *arr, int key, int low, int high, int *comp)
{
	while (low <= high)
	{
		int mid1 = low + (high - low) / 3;
		int mid2 = low + (2 * (high - low)) / 3;
		(*comp)++;
		if (arr[mid1] == key || arr[mid2] == key)
			return 1;
		else if (key < arr[mid1])
			high = mid1 - 1;
		else if (arr[mid1] < key && key < arr[mid2])
		{
			low = mid1 + 1;
			high = mid2 - 1;
		}
		else
			low = mid2 + 1;
	}
	return 0;
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

int main()
{
	int *arr;
	arr = (int *)calloc(Max_size, sizeof(int));
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

	int choose = 0, sort = 0;
	while (choose != 4)
	{
		printf("\nOperations:- \n"
			   "\t1.Linear Search\n"
			   "\t2.Binary Serach\n"
			   "\t3.Ternary Search\n"
			   "\t4.exit\n"
			   "choose above:- ");
		scanf("%d", &choose);
		int key, index, comp = 0;
		switch (choose)
		{

		case 1:
			printf("Enter key value:- ");
			scanf("%d", &key);
			fflush(stdin);
			index = Linera_search(arr, size, key, &comp);
			if (!index)
				printf("\n%d is not found\n", key);
			else
				printf("\n%d is found\n%d comparision\n", key, comp);
			break;

		case 2:
			if (sort == 0)
				Insertion_sort(arr, size);
			sort = 1;
			printf("Enter key value:- ");
			scanf("%d", &key);
			fflush(stdin);
			index = Binary_search(arr, key, 0, size - 1, &comp);
			if (!index)
				printf("\n%d is not found\n", key);
			else
				printf("\n%d is found\n%d comparision\n", key, comp);
			break;

		case 3:
			if (sort == 0)
				Insertion_sort(arr, size);
			sort = 1;
			printf("Enter key value:- ");
			scanf("%d", &key);
			fflush(stdin);
			index = Ternary_search(arr, key, 0, size - 1, &comp);
			if (!index)
				printf("\n%d is not found\n", key);
			else
				printf("\n%d is found\n%d comparision\n", key, comp);
			break;

		case 4:
			printf("you are exit!\n");
			break;

		default:
			printf("you choose wrong option !please try again\n");
			break;
		}
	}
	fclose(fptr);

	return 0;
}
