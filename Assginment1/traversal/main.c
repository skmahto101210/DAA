#include <stdio.h>
#include <stdlib.h>
#define Max_Size 100

typedef struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node *createNode(int val)
{
	Node *new = (Node *)malloc(sizeof(Node));
	new->data = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

Node *BST_Recursively(Node *root, int val)
{
	if (root)
	{
		if (root->data >= val)
			root->left = BST_Recursively(root->left, val);
		if (root->data < val)
			root->right = BST_Recursively(root->right, val);
		return root;
	}
	return createNode(val);
}

Node *BST_NonRecursively(Node *root, int val)
{
	Node *temp = root;
	if (temp == NULL)
		return createNode(val);
	while (temp)
	{
		if (temp->left == NULL && temp->data >= val)
		{
			temp->left = createNode(val);
			break;
		}
		if (temp->right == NULL && temp->data < val)
		{
			temp->right = createNode(val);
			break;
		}
		if (temp->data >= val)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return root;
}

void levelorder_traversal(Node *root, int size, FILE *fptr)
{
	if (root)
	{
		Node **queue;
		queue = (Node **)calloc(size, sizeof(Node *));
		for (int i = 0; i < size; i++)
			queue[i] = (Node *)malloc(sizeof(Node));
		int f = 0, r = 0;
		queue[r++] = root;
		while (f < r)
		{
			Node *temp = queue[f++];
			fprintf(fptr, "%d ", temp->data);
			if (temp->left)
				queue[r++] = temp->left;
			if (temp->right)
				queue[r++] = temp->right;
		}
		free(queue);
	}
}

void preorder_traversal(Node *root, FILE *fptr)
{
	if (root)
	{
		fprintf(fptr, "%d ", root->data);
		preorder_traversal(root->left, fptr);
		preorder_traversal(root->right, fptr);
	}
}

void inorder_traversal(Node *root, FILE *fptr)
{
	if (root)
	{
		inorder_traversal(root->left, fptr);
		fprintf(fptr, "%d ", root->data);
		inorder_traversal(root->right, fptr);
	}
}

void postorder_traversal(Node *root, FILE *fptr)
{
	if (root)
	{
		postorder_traversal(root->left, fptr);
		postorder_traversal(root->right, fptr);
		fprintf(fptr, "%d ", root->data);
	}
}

int main()
{
	Node *root = NULL;
	FILE *fptr;
	fptr = fopen("file_input.txt", "r");
	int size = 0;
	while (!feof(fptr))
	{
		int val;
		if (fscanf(fptr, "%d", &val) == 1)
		{
			root=BST_NonRecursively(root,val);
			size++;
		}
	}
	fclose(fptr);

	fptr = fopen("Traversal_output.txt", "wa");

	int choose = 0;
	int *arr = (int *)malloc((size) * sizeof(int));
	while (choose != 5)
	{
		printf("\nOperations:-\n"
			   "\t1.LevelOrder Traversal\n"
			   "\t2.PreOrder Traversal\n"
			   "\t3.Inorder Traversal\n"
			   "\t4.Postorder Traversal\n"
			   "\t5.exit\n"
			   "choose option:- ");
		scanf("%d", &choose);
		fflush(stdin);
		switch (choose)
		{
		case 1:
			fputs("LevelOrder Traversal: ", fptr);
			levelorder_traversal(root, size, fptr);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(Traversal(output).txt)##\n");
			break;
		case 2:
			fputs("PreOrder Traversal: ", fptr);
			preorder_traversal(root, fptr);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(Traversal(output).txt)##\n");
			break;
		case 3:
			fputs("Inorder Traversal: ", fptr);
			inorder_traversal(root, fptr);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(Traversal(output).txt)##\n");
			break;
		case 4:
			fputs("Postorder Traversal: ", fptr);
			postorder_traversal(root, fptr);
			fputs("\n", fptr);
			printf("\n##Output is Successfully... added to file(Traversal(output).txt)##\n");
			break;

		case 5:
			printf("You are exit\n");
			break;
		default:
			printf("You choose wrong option\n!please try again..\n");
		}
	}
	fclose(fptr);

	return 0;
}
