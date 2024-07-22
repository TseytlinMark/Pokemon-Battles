#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"
#ifndef __POKEMON_H_
#define __POKEMON_H_


typedef struct Type_t
{
	char *name;
	int numofpokes;
	int EAM_cntr;
	int EAO_cntr;
	struct Type_t **effective_against_me;
	struct Type_t **effective_against_others;
}Type;

typedef struct BioInfo
{
	double height;
	double weight;
	int attack;
}PokeBio;
typedef struct Pokemon_t
{
	char *name;
	char *info;
	PokeBio *pBio;
	Type *pType;
}Pokemon;


Pok_err_t Add_to_EAMbyPtr(Type *SourceType, Type* DestType);
Pok_err_t Add_to_EAObyPtr(Type *SourceType, Type* DestType);
PokeBio * Create_Bio(double height, double weight, int attack);
Pok_err_t TypeExistsinEA(char * name,Type **effective_against_,int EActr);
void ERASEBIO(PokeBio *BioInfo);
void ERASEEA(Type *typetodeletefrom);
void freeType (element elem);
Type* CreateType(char * name);
void Type_Print(element elem);
Pokemon* Poke_Create(char *name, char *species, double height, double weight, int attack, Type *type);
void  Pokemon_Print(element elem);
void destroyPoke(element elem);









#endif /* __POKEMON_H_ */
