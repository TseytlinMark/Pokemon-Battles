#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

//Hold my List
struct t_Node
{
	element elem;
	Node next;
};
struct t_LinkedList
{
	Node Head;
	Node Tail;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction eqFunc;
};

Node createNewNode(element elem)
{
	Node new = (Node) malloc(sizeof(struct t_Node));
	if (new == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	new->next = NULL;
	new->elem = elem;
	return new;
}
LinkedList createLinkedList(copyFunction copyf, freeFunction freef, printFunction printf, equalFunction equalf)
{
	LinkedList new = (LinkedList)malloc(sizeof(struct t_LinkedList));
	if(new == NULL)
	{printf("No memory available.\n");
	return NULL;}
	new->Head=NULL;
	new->Tail=NULL;
	new->copyFunc=copyf;
	new->freeFunc=freef;
	new->printFunc = printf;
	new->eqFunc = equalf;
	return new;
}
status appendNode(LinkedList llptr, element elem)
{
	if(llptr->Tail == NULL)
	{
		Node new =(Node) malloc(sizeof(struct t_Node));
		if(new == NULL)
		{
			printf("No memory available.\n");
			return failure;
		}
		new->elem=elem;
		llptr->Tail = new;
		if(llptr->Head == NULL)
			llptr->Head = new;
	}
	else
	{
		Node new =(Node) calloc(1,sizeof(struct t_Node));
		if(new == NULL)
		{
			printf("No memory available.\n");
			return failure;
		}
		new->elem=elem;
		llptr->Tail->next = new;
		llptr->Tail= new;
	}
	return success;
}
status deleteNode(LinkedList llptr, element elem)
{
	if(llptr->Head->elem == elem)
	{
		Node temp = llptr->Head->next;
		llptr->freeFunc(llptr->Head->elem);
		free(llptr->Head);
		llptr->Head = temp;
		return success;
	}
	else
	{
		Node prev = llptr->Head;
		Node curr = llptr->Head->next;
		while (curr!= NULL)
		{
			if (curr->elem == elem)
			{
				prev->next=curr->next;
				llptr->freeFunc(curr->elem);
				free(curr);
				return success;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	return failure;

}
void displayList(LinkedList llptr)
{
	Node temp = llptr->Head;
	while(temp != NULL)
	{
		llptr->printFunc(temp->elem);
		temp = temp->next;
	}
}
void destroyList(LinkedList llptr)
{
	status a;
	while(llptr->Head != NULL)
	{
		a = deleteNode(llptr, llptr->Head->elem);
	}
	free(llptr);
}

element searchByKeyInList(LinkedList llptr, element elem)
{
	Node temp = llptr->Head;
	while(temp != NULL)
	{
		if(llptr->eqFunc(temp->elem, elem)==1)
			return temp->elem;
		temp = temp->next;
	}
	return NULL;
}
Node returnLinkedListHead(LinkedList llptr)
{
	if(llptr == NULL)
		return NULL;
	return llptr->Head;
}
element returnNodeElement(Node nd)
{
	if(nd == NULL)
		return NULL;
	return nd->elem;
}
Node returnNextNode(Node nd)
{
	if(nd == NULL)
		return NULL;
	return nd->next;
}










