#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

/* original version */
entry *findName(char lastName[], hash_table *pHead)
{
    int x=hash(lastName);
	entry *e;
	e=pHead->table[x];
    while (e != NULL) {
        if(strcasecmp(e->lastName,lastName)==0)
		return e;
        e = e->pNext;
    }
    return NULL;
}

entry *append(char lastName[], hash_table *e)
{
    /* allocate memory for the new entry and put lastName */
    int x=hash(lastName);
    entry *node;
    node = (entry *) malloc(sizeof(entry));
    node->pNext=e->table[x];
    e->table[x]=node;
    strcpy(node->lastName, lastName);

    return 0;
}

int hash(char *str)
{
    unsigned long hash=5381;
    while(*str != '\0')
    	hash = (hash<<5)+ *str++;
    return hash%42737;
}

hash_table *Create_hashtable(hash_table *t,int size){
	int i=0;
	t->table=(entry **)malloc(sizeof(entry)*size);
	for(i=0;i<size;i++){
	t->table[i]=NULL;
}
return t;
}
