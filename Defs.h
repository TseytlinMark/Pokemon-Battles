#ifndef _DEFS_H_
#define _DEFS_H_
typedef enum
{
	NO_SUCH_POKE_AS_SRC,
	NO_SUCH_POKE_AS_DST,
	POK_NO_ERR,
	Memory_Problem=3,
	POK_ALREADY_EXIST_ERR,
	BIO_NO_MEMORY_ERR,
	POK_LAST_ERR,
	DST_POK_NOT_IN_SRC_EAM,
	DST_POK_NOT_IN_SRC_EAO,
	PRT_SUCCESS,
	PRT_FAIL,
	DST_POK_NOT_EXISTS,
	TYPE_ALREADY_EXISTS_IN_LIST=10,
	ADD_TYPE=11
} Pok_err_t;

typedef enum e_bool { false,true } bool;
typedef enum e_status { success, failure} status;
typedef void* element;
typedef element(*copyFunction)(element);
typedef void (*freeFunction)(element);
typedef void (*printFunction)(element);
typedef int(*equalFunction)(element,element);//1 first Bigger, 0 - same, -1 Second Bigger
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem, element secondElem, int *attackFirst, int *attackSecond);//return the first attack - second attack. also produce the attack of each element, The function transmits the information through the pointers recieved in the function

#endif /* _DEFS_H_ */
