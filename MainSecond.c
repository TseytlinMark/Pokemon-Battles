//#include "LinkedList.h"
#include "Pokemon.h"
#include "BattleByCategory.h"
#include "Defs.h"
#include <stdio.h>
element copyPokemon(element elem)
{
	Pokemon *p1 = (Pokemon *)elem;
	Pokemon *res = (Pokemon *)malloc(sizeof(Pokemon));
	if(res == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	res->name = (char *)malloc((strlen(p1->name)+1)*sizeof(char));
	if(res->name == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	strcpy(res->name, p1->name);
	res->info = (char *)malloc((strlen(p1->info)+1)*sizeof(char));
	if(res->info == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	strcpy(res->info,p1->info);
	res->pBio = Create_Bio(p1->pBio->height, p1->pBio->weight, p1->pBio->attack);
	if(res->pBio == NULL)
	{
		printf("No memory available.\n");
		return NULL;
	}
	res->pType = p1->pType;
	return (element)res;
}
int equal_Attack(element elem1, element elem2)//main
{
	if(elem1 == NULL || elem2 == NULL)
		return 0;
	Pokemon *poke1 = (Pokemon*) elem1;
	Pokemon *poke2 = (Pokemon*) elem2;
	if(poke1->pBio->attack > poke2->pBio->attack)
		return 1;
	if(poke1->pBio->attack < poke2->pBio->attack)
		return -1;
	return 0;
}
char *getPokemonType(element elem)//main
{
	Pokemon *p1 = (Pokemon *)elem;
	return p1->pType->name;
}
//return the first attack - second attack. also produce the attack of each element, The function transmits the information through the pointers recieved in the function
int getpAttackFunction(element elem1, element elem2, int *attackFirst, int *attackSecond)//main
{
	if(elem1 == NULL || elem2 == NULL)
		return 0;
	Pokemon *p1 = (Pokemon *)elem1;
	Pokemon *p2 = (Pokemon *)elem2;
	Pok_err_t info = TypeExistsinEA(p2->pType->name, p1->pType->effective_against_me, p1->pType->EAM_cntr);
	//Check if p1 type is inside EAM of p2
	//if so - attackFirst = p1 attack - 10;
	if(info == TYPE_ALREADY_EXISTS_IN_LIST)
	{
		*attackFirst = p1->pBio->attack - 10;
	}
	else
	{
		*attackFirst = p1->pBio->attack;
	}
	info = TypeExistsinEA(p1->pType->name, p2->pType->effective_against_me, p2->pType->EAM_cntr);
	//Check if p2 type is inside EAM of p1
	//if so - attackSecond = p2 attack - 10;
	if(info == TYPE_ALREADY_EXISTS_IN_LIST)
	{
		*attackSecond = p2->pBio->attack - 10;
	}
	else
	{
		*attackSecond = p2->pBio->attack;
	}
	return *attackFirst - *attackSecond;
}

Type* Type_Search(Type ** types,int types_cntr, char *name)
{
	int result;
	if(types == NULL)
		return NULL;
	else
	{
		for (int i = 0; i < types_cntr; i++)
		{
			char * curr = types[i]->name;
			result = strcmp(curr,name);
			if(result == 0)
				return types[i];
		}
	}
	return NULL;
}

int main(int argc, char **argv)
{
	//argv[1] - number of Types
	//argv[2] - capacity in Type
	//argv[3] - configuration file
	if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
		{
			printf("Wrong Input\n");
			printf("Example of Running Command\n");
			printf("%s <number of Types> <capacity in types> <configuration file>\n", argv[0]);
			return(0);
		}
	Type ** listoftypes = (Type**) malloc(atoi(argv[1]) * sizeof(struct Type_t*));
	if (listoftypes == NULL)
	{
		printf("Memory Problem\n");
		return Memory_Problem;
	}
	Pok_err_t err_code;
	Battle b = NULL;
	int numoftypes = atoi(argv[1]);
	int capacity = atoi(argv[2]);
	int flagfortypes=0;
	int flagforPokes = 0;
	FILE *fp = fopen(argv[3], "r");
	char buffer[300],linei[300];
	char *line,*token,*name,*Info;
	Type *newType;
	while(fgets(buffer, 300, fp))
	{
		line =strtok(buffer,"\r\n");
		strcpy(linei,line);
		//Types
		//Types Initial START
		if(flagfortypes == 1)
		{
			if(strcmp(line,"Pokemons") == 0)
				break;
			//HERE - WE MAKE THE BATTLE - BECAUSE We've HERE THE CATEGORIES LINE - CHAR *
			b = createBattleByCategory(capacity, numoftypes, line, equal_Attack, copyPokemon, destroyPoke, getPokemonType, getpAttackFunction, Pokemon_Print);
			if(b == NULL)
			{
				return 0;
			}
			token = strtok(linei,",");
			for (int i = 0; i < numoftypes; i++)
			{
				//CREATE TYPE
				//ADD IT TO LIST HERE INSIDE, NOT IN C FILE
				newType = CreateType(token);
				listoftypes[i] = newType;
				//if err_code == 3 than problems
				token = strtok(NULL,",");
			}
			flagfortypes = 0;
		}
		if (strcmp(line,"Types")==0)
			flagfortypes = 1;
		//Types Inital END
		//Effective Lists Initial
		if (line[0]=='\t')
		{
			line++;
			token = strtok(line, " ");
			Type *src = Type_Search(listoftypes, numoftypes,token);
			char *effect = "effective-against-";
			int jump = strlen(token) + strlen(effect)+1;
			line = line + jump;
			//EAM-effective-against-me!
			if (line[0]=='m')
			{
				line = line +3;
				token = strtok(line, ",\r");
				while(token != NULL)
				{
					Type *dst = Type_Search(listoftypes, numoftypes,token);
					err_code = Add_to_EAMbyPtr(src, dst);
					token = strtok(NULL,",\r\n");
				}
			}
			//EAO-effective-against-other!!
			else
			{
				line = line +6;
				token = strtok(line, " ,\r");
				while(token != NULL)
				{
					Type *dst = Type_Search(listoftypes, numoftypes,token);
					err_code = Add_to_EAObyPtr(src, dst);
					token = strtok(NULL,",\r\n");
				}
			}
		}
		//Pokemons
		if (flagforPokes == 1)
		{
			double weight, height;
			int attack, i=0;
			Type *newT;
			token = strtok(line, ",");
			int tokenlen = 0;
			while (token != NULL)
			{
				tokenlen = strlen(token);
				if(i == 0)
				{
					name = (char *) malloc((tokenlen+1)*sizeof(char));
					strcpy(name,token);
				}
				if(i==1)
				{
					Info = (char *) malloc((tokenlen+1)*sizeof(char));
					strcpy(Info,token);
				}
				if(i==2)
					height = atof(token);
				if(i==3)
					weight = atof(token);
				if(i==4)
					attack = atoi(token);
				if(i==5)
				{
					newT =Type_Search(listoftypes, numoftypes, token);
				}
				i++;
				token = strtok(NULL,",");
			}
			Pokemon *new = Poke_Create(name, Info, height, weight, attack, newT);
			free(name);
			free(Info);
			if(new == NULL)
			{
				for(int i =0; i< numoftypes; i++)
				{
					freeType(listoftypes[i]);
				}
				destroyBattleByCategory(b);
				free(listoftypes);
				return 0;
			}
			status a = insertObject(b, new);
			destroyPoke(new);

		}
		if (strcmp(buffer,"Pokemons")==0)
			flagforPokes = 1;
	}
	fclose(fp);
	char namesrc[300];	char c = 1;
	char Name[300], species[300];
	double height, weight;
	int attack;
	Type *src = NULL;
	while(c != '$')
	{
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");
		scanf(" %c", &c);
		switch(c){
		case '1':
			if(b != NULL)
				displayObjectsByCategories(b);
			break;
		case '2':
			for(int i =0; i < numoftypes; i++)
			{
				Type_Print(listoftypes[i]);
			}
			break;
		case '3':
			printf("Please enter Pokemon type name:\n");
			scanf("%s", namesrc);
			//We should move Type_Search here
			src = Type_Search(listoftypes, numoftypes,namesrc);
			if (src == NULL)
			{
				printf("Type name doesn't exist.\n");
				break;
			}
			int numOfObjInCat = getNumberOfObjectsInCategory(b, namesrc);
			if(numOfObjInCat == capacity)
			{
				printf("Type at full capacity.\n");
				break;
			}
			printf("Please enter Pokemon name:\n");
			scanf("%s",Name);
			printf("Please enter Pokemon species:\n");
			scanf("%s",species);
			printf("Please enter Pokemon height:\n");
			scanf("%lf", &height);
			printf("Please enter Pokemon weight:\n");
			scanf("%lf", &weight);
			printf("Please enter Pokemon attack:\n");
			scanf("%d", &attack);
			Pokemon *new = Poke_Create(Name, species, height, weight, attack, src);
			status a = insertObject(b, new);
			printf("The Pokemon was successfully added.\n");
			Pokemon_Print(new);
			destroyPoke(new);
			break;
		case '4':
			printf("Please enter type name:\n");
			scanf("%s", namesrc);
			src = Type_Search(listoftypes, numoftypes,namesrc);
			if (src == NULL)
			{
				printf("Type name doesn't exist.\n");
				break;
			}
			element elem = removeMaxByCategory(b, namesrc);
			if(elem == NULL)
			{
				printf("There is no Pokemon to remove.\n");
				break;
			}
			printf("The strongest Pokemon was removed:\n");
			Pokemon_Print(elem);
			Pokemon* poke = (Pokemon*) elem;
			int numofType = poke->pType->numofpokes;
			poke->pType->numofpokes = numofType -1;
			destroyPoke(elem);
			break;
		case '5':
			printf("Please enter Pokemon type name:\n");
			scanf("%s", namesrc);
			src = Type_Search(listoftypes, numoftypes,namesrc);
			if (src == NULL)
			{
				printf("Type name doesn't exist.\n");
				break;
			}
			printf("Please enter Pokemon name:\n");
			scanf("%s",name);
			printf("Please enter Pokemon species:\n");
			scanf("%s", species);
			printf("Please enter Pokemon height:\n");
			scanf("%lf", &height);
			printf("Please enter Pokemon weight:\n");
			scanf("%lf", &weight);
			printf("Please enter Pokemon attack:\n");
			scanf("%d", &attack);
			new = Poke_Create(name, species, height, weight, attack, src);
			element returned = fight(b, new);
			if(returned == NULL)
			{
				destroyPoke(new);
				break;
			}
			else if((Pokemon*)returned != new)
			{
				destroyPoke(returned);
				destroyPoke(new);
				break;

			}
			destroyPoke(new);
			break;
		case '6' :
			printf("All the memory cleaned and the program is safely closed.\n");
			for(int i =0; i< numoftypes; i++)
			{
				freeType(listoftypes[i]);
			}
			free(listoftypes);
			if (b == NULL)
			{
				c= '$';
				break;
			}
			destroyBattleByCategory(b);
			c= '$';
			break;
		default:
			printf("Please choose a valid number.\n");
			break;
		}
	}
	return 0;
}

