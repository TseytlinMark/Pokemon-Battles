#ifndef BATTLEBYCATEGORY_H_
#define BATTLEBYCATEGORY_H_
#include "Defs.h"

typedef struct battle_s* Battle;

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement);//DONE
status destroyBattleByCategory(Battle b);//DONE
status insertObject(Battle b, element elem);//DONE
void displayObjectsByCategories(Battle b);//DONE
element removeMaxByCategory(Battle b,char* category);//DONE
int getNumberOfObjectsInCategory(Battle b,char* category);//DONE
element fight(Battle b,element elem);


#endif /* BATTLEBYCATEGORY_H_ */
