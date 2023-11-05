#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListHeadNode
{
	int value;
	struct ListHeadNode* left;
	struct ListHeadNode* right;
	struct ListHeadNode* down;
};

struct TreeNode
{
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct QueueNode
{
	int value;
	struct QueueNode* next;
};

struct QueueNode* createQueueNode(int n)
{
	struct QueueNode* vertex = (struct QueueNode*) malloc(sizeof(struct QueueNode));
	if (vertex)
	{
		vertex->value = n;
		vertex->next = NULL;
	}
	return vertex;
}

void queuePush(struct QueueNode** queue, int n)
{
	if (*queue == NULL)
	{
		*queue = createQueueNode(n);
	}
	else
	{
		queuePush(&(*queue)->next, n);
	}
}

struct QueueNode* queuePop(struct QueueNode** queue)
{
	if (*queue == NULL)
	{
		return NULL;
	}
	else
	{
		struct QueueNode* temp = *queue;
		*queue = (*queue)->next;
		return temp;
	}
}

struct TreeNode* createTreeNode(int n)
{
	struct TreeNode* vertex = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	if (vertex)
	{
		vertex->value = n;
		vertex->left = NULL;
		vertex->right = NULL;
	}
	return vertex;
}

void insertVisited(struct TreeNode** visited, int n)
{
	if (*visited == NULL)
	{
		*visited = createTreeNode(n);
	}
	else
	{
		if (n <= (*visited)->value)
		{
			insertVisited(&(*visited)->left, n);
		}
		else
		{
			insertVisited(&(*visited)->right, n);
		}
	}
}

bool isVisited(struct TreeNode** visited, int n)
{
	if (*visited == NULL)
	{
		return false;
	}
	else if ((*visited)->value == n)
	{
		return true;
	}
	else
	{
		if (n <= (*visited)->value)
		{
			isVisited(&(*visited)->left, n);
		}
		else
		{
			isVisited(&(*visited)->right, n);
		}
	}
}

struct ListHeadNode* createNode(int n)
{
	struct ListHeadNode* vertex = (struct ListHeadNode*) malloc(sizeof(struct ListHeadNode));
	if (vertex)
	{
		vertex->value = n;
		vertex->left = NULL;
		vertex->right = NULL;
		vertex->down = NULL;
	}
	return vertex;
}

void insertNode(struct ListHeadNode** array, int n)
{
	if (*array == NULL)
	{
		*array = createNode(n);
	}
	else if ((*array)->right == NULL)
	{
		(*array)->right = createNode(n);
		(*array)->right->left = (*array);
	}
	else
	{
		insertNode(&(*array)->right, n);
	}
}

void insertChild(struct ListHeadNode** array, int m)
{
	if ((*array)->down == NULL)
	{
		(*array)->down = createNode(m);
	}
	else
	{
		insertChild(&(*array)->down, m);
	}
}

void insertSingleEdge(struct ListHeadNode** array, int n, int m)
{
	if (*array == NULL)
	{
		return;
	}
	else if ((*array)->value == n)
	{
		insertChild(array, m);
	}
	else
	{
		insertSingleEdge(&(*array)->right, n, m);
	}
}

void insertEdge(struct ListHeadNode** array, int n, int m)
{
	insertSingleEdge(array, n, m);
	insertSingleEdge(array, m, n);
}

struct ListHeadNode** childHeadNode(struct ListHeadNode** array, int n)
{
	while ((*array)->left)
	{
		(*array) = (*array)->left;
	}

	while ((*array))
	{
		if ((*array)->value == n)
		{
			return array;
		}
		else
		{
			(*array) = (*array)->right;
		}
	}

	return NULL;
}

void printList(struct ListHeadNode* array)
{
	while (array != NULL)
	{
		printf("Wierzcholek %d: ", array->value);
		struct ListHeadNode* bottom = array->down;
		while (bottom != NULL)
		{
			printf("%d ", bottom->value);
			bottom = bottom->down;
		}
		printf("\n");
		array = array->right;
	}
}

void bfsSingle(struct ListHeadNode** array, struct TreeNode** visited, struct QueueNode** queue)
{
	struct ListHeadNode* temp = (*array);
	queuePush(queue, temp->value);
	while (*queue)
	{
		struct ListHeadNode** vertexAddr = childHeadNode(array, (*queue)->value);
		struct ListHeadNode* vertex = *vertexAddr;
		queuePop(queue);
		if (!isVisited(visited, vertex->value))
		{
			printf("Odwiedzono wierzcholek %d\n", vertex->value);
			insertVisited(visited, vertex->value);
		}

		while (vertex->down)
		{
			vertex = vertex->down;
			if (!isVisited(visited, vertex->value))
			{
				queuePush(queue, vertex->value);
			}
		}
	}
}

void breadthFirstSearch(struct ListHeadNode** array)
{
	struct TreeNode* visited = NULL;
	struct QueueNode* queue = NULL;
	bfsSingle(array, &visited, &queue);
}

int main(void)
{
	struct ListHeadNode* array = NULL;

	insertNode(&array, 0);
	insertNode(&array, 1);
	insertNode(&array, 2);
	insertNode(&array, 3);
	insertNode(&array, 4);

	insertEdge(&array, 3, 4);
	insertEdge(&array, 2, 3);
	insertEdge(&array, 2, 0);
	insertEdge(&array, 1, 2);

	printList(array);

	breadthFirstSearch(&array);

	return 0;
}