#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct t_Node *Node;
typedef struct t_LinkedList *LinkedList;
typedef void* element;
typedef element(*copyFunction)(element);
typedef void (*freeFunction)(element);
typedef void (*printFunction)(element);
typedef int(*equalFunction)(element,element);



LinkedList createLinkedList(copyFunction copyf, freeFunction freef, printFunction printf, equalFunction equalf);
Node createNewNode(element pType);
status appendNode(LinkedList llptr, element elem);
status deleteNode(LinkedList llptr, element elem);
void displayList(LinkedList llptr);
void destroyList(LinkedList llptr);
element searchByKeyInList(LinkedList llptr, element elem);
Node returnLinkedListHead(LinkedList llptr);
element returnNodeElement(Node nd);
Node returnNextNode(Node nd);





#endif /* LINKEDLIST_H_ */
