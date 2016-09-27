#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */

#define OPT 1
typedef struct __PHONE_BOOK_DETAIL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_DETAIL *pNext;
} detail;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *book_detail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct hash_table {
    entry **table;
} hash_table;

entry *findName(char lastName[], hash_table *pHead);
entry *append(char lastName[], hash_table *e);
int hash(char *str);
hash_table *Create_hashtable(hash_table *t,int size);

#endif
