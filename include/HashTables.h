#ifndef _HASH_TABLES_H
#define _HASH_TABLES_H
#include <LouDDK.h>

#define hash_init(table) __hash_init(table, HASH_SIZE(table))
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)

typedef struct _HLIST_NODE {
    PListHeader Neighbors;
}HLIST_NODE, * PHLIST_NODE;

typedef struct _HLIST_HEAD{
	PHLIST_NODE first;
}HLIST_HEAD, * PHLIST_HEAD;

static inline void __hash_init(PHLIST_HEAD ht, unsigned int sz){
	unsigned int i;

	for (i = 0; i < sz; i++){
		ht[i].first = 0x00;
    }
}



#endif