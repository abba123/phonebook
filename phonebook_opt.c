#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

/* original version */
entry *findName(char lastName[], entry *pHead)
{
    unsigned long x=hash(lastName);
    while (pHead != NULL) {
        if(x==pHead->hash_num) {
            while(pHead != NULL) {
                pHead=pHead->pNext;
                if (strcasecmp(lastName, pHead->lastName) == 0)
                    return pHead;
                pHead=pHead->pNext;
            }
        }
        pHead = pHead->pHash;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    unsigned long x=hash(lastName);
    printf("%s",lastName);
    while(e->pHash!=NULL) {
        e=e->pHash;
        if(e->hash_num==x) {
            entry *node=(entry *)malloc(sizeof(entry));
            node->hash_num=x;
            strcpy(node->lastName,lastName);
            node->pNext=e->pNext;
            e->pNext=node;
            return 0;
        }
    }
    e->pHash = (entry *) malloc(sizeof(entry));
    e = e->pHash;
    strcpy(e->lastName, lastName);
    e->hash_num=hash(lastName);
    e->pNext = NULL;
    e->pHash = NULL;

    return 0;
}

unsigned long hash(char *str)
{
    unsigned long hash=5381;
    int c;
    c=*str++;
    hash = ((hash<<5)+hash)+c;
    return hash;
}
