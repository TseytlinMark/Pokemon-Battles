#include <stdio.h>
#include <stdlib.h>
#include "BattleByCategory.h"
#include "MaxHeap.h"
#include "LinkedList.h"
struct battle_s
{
	LinkedList categorieslist;
	int capacity;
	int numberofCategories;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction eqFunc;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
};
element copyHeapForList(element e)
{MaxHeap mh = (MaxHeap) e;
return copyHeap(mh);}
void destroyHeapforList(element e)
{MaxHeap mh = (MaxHeap) e;
return destroyHeap(mh);}
void printHeapforList(element e)
{MaxHeap mh = (MaxHeap)e;
return printHeap(mh);}
int cmpHeapForList(element e1, element e2)
{MaxHeap mh = (MaxHeap) e1;
return HeapEQ(mh, e2);}
Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement)
{
	if(categories == NULL || equalElement == NULL || copyElement == NULL || freeElement==NULL || getCategory == NULL || getAttack == NULL || printElement == NULL)
		return NULL;
	Battle new = (Battle) malloc (sizeof(struct battle_s));
	if(new == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	new->copyFunc =copyElement;
	new->eqFunc =equalElement;
	new->freeFunc =freeElement;
	new->getAttack = getAttack;
	new->getCategory =getCategory;
	new->printFunc=printElement;
	new->numberofCategories = numberOfCategories;
	new->capacity = capacity;
	new->categorieslist = createLinkedList(copyHeapForList, destroyHeapforList, printHeapforList, cmpHeapForList);
	if(new->categorieslist == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	status a;
	//SPLITING Categories
	char *token;
	token = strtok(categories, ",");
	while(token != NULL)
	{
		a = appendNode((element)new->categorieslist, createHeap(copyElement, freeElement, printElement, equalElement, token, capacity));
		token = strtok(NULL,",");
	}
	return new;
}
//Need to work through getCategoryFunction
status insertObject(Battle b, element elem)
{
	if(b == NULL || elem == NULL)
		return failure;
	//Check for correct print output scenarios
	element final = b->copyFunc(elem);
	char *elemcategory = b->getCategory(elem);
	element found = searchByKeyInList((LinkedList)b->categorieslist, elemcategory);
	if(found !=NULL)
	{
		status a = insertToHeap((MaxHeap)found, final);
		return a;
	}
	return failure;
}
void displayObjectsByCategories(Battle b)
{
	displayList(b->categorieslist);
}
status destroyBattleByCategory(Battle b)
{
	destroyList(b->categorieslist);
	free(b);
	return success;
}
element removeMaxByCategory(Battle b,char* category)
{
	element found = searchByKeyInList((LinkedList)b->categorieslist, category);
	return (element)PopMaxHeap(found);
}
int getNumberOfObjectsInCategory(Battle b,char* category)
{
	element found = searchByKeyInList((LinkedList)b->categorieslist, category);
	return getHeapCurrentSize(found);
}
element fight(Battle b, element elem)
{
	int *tempfirstattack = (int*) malloc(sizeof(int));
	if (tempfirstattack == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	int *tempsecondattack = (int*) malloc(sizeof(int));
	if(tempsecondattack == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	int firstattack = 0;
	int secondattack;
	int attdiff = 0;
	element Strongest;
	element tempStrongest;
	Node TempPtr = returnLinkedListHead(b->categorieslist);
	Strongest = TopMaxHeap(returnNodeElement(TempPtr));
	if(Strongest != NULL)
	{
		attdiff = b->getAttack(Strongest, elem, tempfirstattack, tempsecondattack);
		firstattack = *tempfirstattack;
		secondattack = *tempsecondattack;
	}
	//IN CASE THAT FIRST HEAP IS EMPTY,INITIALIZE ATTDIFF TO MINIMAL VALUE
	if(Strongest == NULL)
		attdiff = -10000;
	while(TempPtr !=NULL)
	{
		TempPtr = returnNextNode(TempPtr);
		if(TempPtr == NULL)
			break;
		tempStrongest = TopMaxHeap(returnNodeElement(TempPtr));
		if(tempStrongest != NULL)
		{
			if(b->getAttack(tempStrongest, elem, tempfirstattack, tempsecondattack) > attdiff)
			{
				attdiff = b->getAttack(tempStrongest, elem, tempfirstattack, tempsecondattack);
				Strongest = tempStrongest;
				firstattack = *tempfirstattack;
				secondattack = *tempsecondattack;
			}
		}
	}
	free(tempfirstattack);
	free(tempsecondattack);
	printf("You choose to fight with:\n");
	b->printFunc(elem);
	if(Strongest == NULL)
	{
		printf("There are no Pokemons to fight against you.\n");
		return NULL;
	}
	printf("The final battle between:\n");
	b->printFunc(elem);
	printf("In this battle his attack is :%d\n\n", secondattack);
	printf("against ");
	b->printFunc(Strongest);
	printf("In this battle his attack is :%d\n\n", firstattack);
	if(attdiff > 0)
	{
		printf("THE WINNER IS:\n");
		b->printFunc(Strongest);
		element returnable = b->copyFunc(Strongest);
		return returnable;
	}
	if(attdiff < 0)
	{
		printf("THE WINNER IS:\n");
		b->printFunc(elem);
		return elem;
	}
	if(attdiff == 0)
	{
		printf("IT IS A DRAW.\n");
	}

	element returnable= b->copyFunc(Strongest);
	return returnable;
}
