
#ifndef DTAB
#define DTAB

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/****************************** STRING HASHING *******************************/
typedef uint64_t dtab_hash_t;
extern uint64_t dtab_hash_djb2(const char * str); // slightly faster
extern uint64_t dtab_hash_sdbm(const char * str);
#define DTAB_HASH(name) dtab_hash_djb2(name)

/********************** DTAB: DYNAMIC HASH TABLE FOR C99 v0.1 ******************/
#define DTAB_LEN_INIT 16

// DTAB_INIT: a dtab is two arrays: list of name hashes (keys) and list of values.
struct dtab {
    dtab_hash_t * keys;
    void * values;
    size_t len;
    size_t num;
};

#define DTAB_INIT(dtab_ptr, type) dtab_ptr = malloc(sizeof(*dtab_ptr));\
dtab_ptr->len = DTAB_LEN_INIT;\
dtab_ptr->num = 0;\
dtab_ptr->values = calloc((DTAB_LEN_INIT), sizeof(type));\
dtab_ptr->keys = malloc(sizeof(*dtab_ptr->keys)*(DTAB_LEN_INIT));\



#endif /* DARR */