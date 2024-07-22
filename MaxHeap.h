#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct t_MaxHeap *MaxHeap;
typedef void* element;
typedef element(*copyFunction)(element);
typedef void (*freeFunction)(element);
typedef void (*printFunction)(element);
typedef int(*equalFunction)(element,element);

MaxHeap createHeap(copyFunction copyf, freeFunction freef, printFunction printf, equalFunction equalf, char *name, int maxsize);
void destroyHeap(MaxHeap mhPtr);
status insertToHeap(MaxHeap mhPtr, element elem);
void printHeap(MaxHeap mhPtr);
element PopMaxHeap(MaxHeap mhPtr);
element TopMaxHeap(MaxHeap mhPtr);
char * getHeapId(MaxHeap mhPtr);
int getHeapCurrentSize(MaxHeap mhPtr);
MaxHeap copyHeap(MaxHeap mhPtr);
int HeapEQ(MaxHeap mhPtr1, element elem);

#endif /* MAXHEAP_H_ */
