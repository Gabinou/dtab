
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

// DTAB_INIT: a dtab is a struct with two arrays: list of name hashes (keys) and list of values.
// they have len total allocated length and num active elements.
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

#define DTAB_ADD(dtab_ptr, name, value) dtab_ptr->keys[dtab_ptr->num] = DTAB_HASH(name);\
dtab_ptr->values[dtab_ptr->num]
#define DTAB_GET(dtab_ptr, name) 
#define DTAB_FREE(dtab_ptr) 
#define DTAB_DEL(dtab_ptr, name) 
#define DTAB_GROW(dtab_ptr) 
#define DTAB_REALLOC(dtab_ptr) 
#define DTAB_LEN(dtab_ptr) dtab_ptr->len 
#define DTAB_NUM(dtab_ptr) dtab_ptr->num


#endif /* DARR */