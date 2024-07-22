#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "MaxHeap.h"
struct t_MaxHeap
{
	element *array;
	char *name;
	int maxsize;
	int currsize;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction eqFunc;
};

MaxHeap createHeap(copyFunction copyf, freeFunction freef, printFunction printf, equalFunction equalf, char *name, int maxsize)
{
	MaxHeap new = (MaxHeap) malloc(sizeof(struct t_MaxHeap));
	if(new == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	new->maxsize = maxsize;
	new->array = (element*) malloc(maxsize * sizeof(element));
	//Memory Problem
	if(new->array == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	int namelen = strlen(name);
	new->name = (char *) malloc (sizeof(char)*(namelen+1));
	//Memory Problem
	if(new->name == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	strcpy(new->name,name);
	new->copyFunc = copyf;
	new->freeFunc = freef;
	new->printFunc = printf;
	new->eqFunc = equalf;
	new->currsize = 0;
	return new;
}

int parent(int pos) { return (pos) / 2; }
int leftChild(int pos) { return (2 * pos); }
int rightChild(int pos) {return (2 * pos) + 1; }
int isLeaf(MaxHeap mhPtr, int pos)
{
	if (pos >= (mhPtr->currsize / 2) && pos <= mhPtr->currsize) {
		return 1;
	}
	return 0;
}
void HeapifyUp(MaxHeap mhPtr, int pos)
{
	element temp = mhPtr->array[pos];
	while(pos > 0 && mhPtr->eqFunc(temp, mhPtr->array[parent(pos)])==1)
	{
		mhPtr->array[pos] = mhPtr->array[parent(pos)];
		pos = parent(pos);
	}
	mhPtr->array[pos] = temp;
}
void swap(MaxHeap mhPtr, int fpos, int spos)
{
	element temp;
	temp = mhPtr->array[fpos];
	mhPtr->array[fpos] = mhPtr->array[spos];
	mhPtr->array[spos] = temp;
}

status insertToHeap(MaxHeap mhPtr, element elem)
{
	if(mhPtr->currsize < mhPtr->maxsize)
	{
		mhPtr->array[mhPtr->currsize] = elem;
		HeapifyUp(mhPtr, mhPtr->currsize);
		mhPtr->currsize++;
		return success;
	}
	else
		return failure;
}
void downHeapify(MaxHeap mhPtr, int pos) {
	if (pos >= (mhPtr->currsize / 2) && pos <= mhPtr->currsize)
		return;
	if(mhPtr->eqFunc(mhPtr->array[pos],mhPtr->array[leftChild(pos)]) == -1 || mhPtr->eqFunc(mhPtr->array[pos],mhPtr->array[rightChild(pos)]) == -1 )
	{
		if(mhPtr->eqFunc(mhPtr->array[leftChild(pos)], mhPtr->array[rightChild(pos)])== 1)
		{
			swap(mhPtr, pos, leftChild(pos));
			downHeapify(mhPtr, leftChild(pos));
		}
		else
		{
			swap(mhPtr, pos, rightChild(pos));
			downHeapify(mhPtr, rightChild(pos));
		}
	}
}
//WHAT HAPPENS TO FREE MEMORY ??
element PopMaxHeap(MaxHeap mhPtr)
{
	if(mhPtr->currsize == 0)
		return NULL;
	element ret = mhPtr->array[0];
	mhPtr->array[0] = mhPtr->array[mhPtr->currsize -1];
	downHeapify(mhPtr, 0);
	mhPtr->array[mhPtr->currsize-1] = NULL;
	mhPtr->currsize--;
	return ret;
}
element TopMaxHeap(MaxHeap mhPtr)
{
	if(mhPtr->currsize == 0)
		return NULL;
	return mhPtr->array[0];
}
char * getHeapId(MaxHeap mhPtr)
{
	return mhPtr->name;
}
int getHeapCurrentSize(MaxHeap mhPtr)
{
	return mhPtr->currsize;
}
void printHeap(MaxHeap mhPtr)
{
	MaxHeap res = copyHeap(mhPtr);
	printf("%s:\n", res->name);
	if(res->currsize == 0)
		printf("No elements.\n\n");
	else
	{
		//Sorting Heap-Descending
		for(int i =0; i< res->currsize; i++)
		{
			for(int j=0; j < res->currsize; j++)
			{
				if(res->eqFunc(res->array[j], res->array[i]) == -1)
				{
					swap(res,i,j);
				}
			}
		}
		for(int i = 0; i< res->currsize; i++)
		{
			printf("%d. ", i+1);
			res->printFunc(res->array[i]);
		}
	}
	free(res->array);
	free(res->name);
	free(res);
}
void destroyHeap(MaxHeap mhPtr)
{
	for(int i=0; i<mhPtr->currsize; i++)
	{
		mhPtr->freeFunc(mhPtr->array[i]);
	}
	free(mhPtr->array);
	free(mhPtr->name);
	free(mhPtr);

}
MaxHeap copyHeap(MaxHeap mhPtr)
{
	MaxHeap res = (MaxHeap)malloc(sizeof(struct t_MaxHeap));
	if(res==NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	res->name = (char *)malloc((strlen(mhPtr->name)+1)*sizeof(char));
	if(res->name == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	strcpy(res->name, mhPtr->name);
	res->maxsize = mhPtr->maxsize;
	res->array = (element*) malloc(res->maxsize * sizeof(element));
	res->currsize = mhPtr->currsize;
	//Memory Problem
	if(res->array == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	for(int i =0 ; i< res->currsize; i++)
	{
		res->array[i] = mhPtr->array[i];
	}
	res->copyFunc = mhPtr->copyFunc;
	res->freeFunc = mhPtr->freeFunc;
	res->printFunc = mhPtr->printFunc;
	res->eqFunc = mhPtr->eqFunc;
	return res;
}
int HeapEQ(MaxHeap mhPtr1, element elem)
{
	if(strcmp(mhPtr1->name,(char*)elem)==0)
		return 1;
	return 0;
}







