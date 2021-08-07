
#ifndef DTAB
#define DTAB

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/********************** DTAB: DYNAMIC HASH TABLE FOR C99 v0.1 ******************/

/****************************** STRING HASHING *******************************/
uint64_t dtab_hash_djb2(const char * str); // slightly faster
uint64_t dtab_hash_sdbm(const char * str);
#define DTAB_HASH(name) dtab_hash_djb2(name)


#endif /* DARR */