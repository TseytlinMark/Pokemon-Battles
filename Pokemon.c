#include "Pokemon.h"
#include <stdio.h>
Type *new = (Type*) NULL;
int EAMsize;
int EAOSize;

PokeBio * Create_Bio(double height, double weight, int attack)
{
	PokeBio *newbio = (struct BioInfo*) malloc(sizeof(struct BioInfo));
	if (newbio == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	newbio->height = height;
	newbio->weight = weight;
	newbio->attack = attack;
	return newbio;
}
Pok_err_t Add_to_EAMbyPtr(Type *SourceType, Type* DestType)
{

	if(SourceType->effective_against_me == NULL)
	{
		SourceType->effective_against_me = (struct Type_t**) malloc(sizeof(struct Type_t*));
		if(SourceType->effective_against_me == NULL)
		{
			printf("No memory available.\n");
			return Memory_Problem;

		}
		SourceType->effective_against_me[0] = DestType;
	}
	else
	{
		EAMsize = SourceType->EAM_cntr;
		SourceType->effective_against_me = (Type**) realloc(SourceType->effective_against_me, ((EAMsize + 1) * (sizeof(struct Type_t*))));
		if(SourceType->effective_against_me == NULL)
		{
			printf("No memory available.\n");
			return Memory_Problem;

		}
		SourceType->effective_against_me[EAMsize] = DestType;
	}
	SourceType->EAM_cntr++;
	return POK_NO_ERR;
}

Pok_err_t Add_to_EAObyPtr(Type *SourceType, Type* DestType)
{

	if(SourceType->effective_against_others == NULL)
	{
		SourceType->effective_against_others = (struct Type_t**) malloc(sizeof(struct Type_t*));
		if(SourceType->effective_against_others == NULL)
		{
			printf("No memory available.\n");
			return Memory_Problem;

		}
		SourceType->effective_against_others[0] = DestType;
	}
	else
	{
		int EAOsize = SourceType->EAO_cntr;
		SourceType->effective_against_others = (Type**) realloc(SourceType->effective_against_others, ((EAOsize + 1) * (sizeof(struct Type_t*))));
		if(SourceType->effective_against_others == NULL)
		{
			printf("No memory available.\n");
			return Memory_Problem;

		}
		SourceType->effective_against_others[EAOsize] = DestType;
	}
	SourceType->EAO_cntr++;
	return POK_NO_ERR;
}
void  Pokemon_Print(element elem)
{
	Pokemon *pokemon = (Pokemon*) elem;
	if(pokemon == NULL)
		return;
	else
	{
		printf("%s :\n", pokemon->name);
		printf("%s, %s Type.\n", pokemon->info, (pokemon->pType->name));
		printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", (pokemon->pBio->height), (pokemon->pBio->weight),(pokemon->pBio->attack));
	}
}
Pok_err_t TypeExistsinEA(char * name, Type **effective_against_, int EActr)
{
	for(int i = 0; i< EActr; i++)
	{
		if (strcmp((effective_against_[i]->name),name)==0)
			return TYPE_ALREADY_EXISTS_IN_LIST;
	}
	return ADD_TYPE;
}
void ERASEEA(Type *typetodeletefrom)
{
	for (int i = 0; i < typetodeletefrom->EAM_cntr; i++)
	{
		if(typetodeletefrom->effective_against_me[i] != NULL)
		{
			typetodeletefrom->effective_against_me[i]= NULL;
		}
	}
	free (typetodeletefrom->effective_against_me);
	typetodeletefrom->effective_against_me = NULL;
	for (int i = 0; i < typetodeletefrom->EAO_cntr; i++)
	{
		if(typetodeletefrom->effective_against_others[i] != NULL)
		{
			typetodeletefrom->effective_against_others[i]= NULL;
		}
	}
	free (typetodeletefrom->effective_against_others);
	typetodeletefrom->effective_against_others = NULL;
}
void ERASEBIO(PokeBio *BioInfo)
{
	free(BioInfo);
}
Type* CreateType(char * name)
{
	new = (struct Type_t*) calloc(1,sizeof(struct Type_t));
	if (new == NULL)
	{
		printf("Memory Problem\n");
		return NULL;
	}
	int namelen = strlen(name);
	new->name = (char*) malloc(sizeof(char)*(namelen+1));
	if(new->name == NULL)
	{
		printf("Memory Problem\n");
		return NULL;

	}
	strcpy(new->name, name);
	new->effective_against_me = NULL;
	new->effective_against_others = NULL;
	new->numofpokes=0;
	new->EAM_cntr=0;
	new->EAO_cntr=0;
	return new;
}
void freeType (element elem)
{
	Type *type = (Type*) elem;
	free(type->name);
	ERASEEA(type);
	type->effective_against_me = NULL;
	type->effective_against_others = NULL;
	free(type);
}
void Type_Print(element elem)
{
	Type *type = (Type *)elem;
	printf("Type %s -- %d pokemons\n", type->name, type->numofpokes);
	if(type->EAM_cntr != 0)
	{
		printf("\tThese types are super-effective against %s:", type->name);
		for (int i=0; i<type->EAM_cntr;i++)
		{
			if(i==type->EAM_cntr-1)
				printf("%s\n", type->effective_against_me[i]->name);

			else
				printf("%s ,", type->effective_against_me[i]->name);
		}
	}
	if(type->EAO_cntr != 0)
	{
		printf("\t%s moves are super-effective against:",type->name);
		for (int i =0; i<type->EAO_cntr;i++)
		{
			if(i==type->EAO_cntr-1)
				printf("%s\n", type->effective_against_others[i]->name);

			else
				printf("%s ,", type->effective_against_others[i]->name);
		}
	}
	printf("\n");
}

Pokemon* Poke_Create(char *name, char *species, double height, double weight, int attack, Type *type)
{
	Pokemon *new = (struct Pokemon_t*) calloc(1,sizeof(struct Pokemon_t));
	if (new == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	int namelen = strlen(name);
	new->name = (char*) malloc(sizeof(char)*(namelen+1));
	if(new->name == NULL)
	{
		printf("No memory available.\n");
		return NULL;

	}
	strcpy(new->name, name);
	int specieslen = strlen(species);
	new->info = (char*) malloc(sizeof(char)*(specieslen+1));
	if(new->info == NULL)
	{
		printf("No memory available.\n");
		return NULL;

	}
	strcpy(new->info, species);
	new->pBio = (Create_Bio(height,weight,attack));
	if(new->pBio == NULL)
		return NULL;
	new->pType = type;
	new->pType->numofpokes++;
	return new;
}
void destroyPoke(element elem)
{
	Pokemon * poke = (Pokemon*) elem;
	PokeBio *Bio = poke->pBio;
	ERASEBIO(Bio);
	poke->pBio = NULL;
	free(poke->name);
	free(poke->info);
	free(poke);
}



