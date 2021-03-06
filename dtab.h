#ifndef DTAB
#define DTAB

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/********************* DTAB: DYNAMIC HASH TABLE FOR C99 v1.0 *****************/
typedef unsigned char dtab_byte_t; // for convenience

extern uint64_t dtab_hash_djb2(const char * str); // slightly faster
extern uint64_t dtab_hash_sdbm(const char * str);
#define DTAB_HASH(name) dtab_hash_djb2(name)

#define DTAB_LEN_INIT 16
#define DTAB_NUM_INIT 1
#define DTAB_NULL 0
#define DTAB_GROWTH_FACTOR 2

struct dtab {
    size_t bytesize;
    size_t len; /* allocated length */
    size_t num; /* number of active elements (num < len) */
    uint64_t * keys;
    void * values;
};

extern void * dtab_get(struct dtab * dtab_ptr, uint64_t in_hash);
extern void dtab_add(struct dtab * dtab_ptr, void * value, uint64_t in_hash);
extern size_t dtab_found(struct dtab * dtab_ptr, uint64_t in_hash);
extern void dtab_del(struct dtab * dtab_ptr, uint64_t in_hash);
extern void dtab_del_scramble(struct dtab * dtab_ptr, uint64_t in_hash);

#define DTAB_STRINGIFY(name) #name

#define DTAB_INIT(dtab_ptr, type) dtab_ptr = malloc(sizeof(*dtab_ptr));\
dtab_ptr->len = DTAB_LEN_INIT;\
dtab_ptr->num = DTAB_NUM_INIT;\
dtab_ptr->values = calloc(DTAB_LEN_INIT, sizeof(type));\
dtab_ptr->keys = malloc(sizeof(*dtab_ptr->keys) * (DTAB_LEN_INIT));\
dtab_ptr->keys[DTAB_NULL] = DTAB_NULL;\
dtab_ptr->bytesize = sizeof(type);
#define DTAB_GROW(dtab_ptr)  do {\
    dtab_ptr->len*=DTAB_GROWTH_FACTOR;\
    dtab_ptr->keys = realloc(dtab_ptr->keys, dtab_ptr->len * sizeof(uint64_t));\
    dtab_ptr->values = realloc(dtab_ptr->values, dtab_ptr->len * dtab_ptr->bytesize);} while(0)
#define DTAB_FREE(dtab_ptr) do {free(dtab_ptr->keys) ;\
free(dtab_ptr->values);\
free(dtab_ptr); } while(0)

/* DTAB macros hash the input strings everytime.
Might be faster to put hash in variable and call functions directly?
S for stringify, H for hash */

#define DTAB_ADD(dtab_ptr, value, key) dtab_add(dtab_ptr, value, key)
#define DTAB_ADDS(dtab_ptr, value, name) dtab_add(dtab_ptr, value, DTAB_HASH(DTAB_STRINGIFY(name)))
#define DTAB_ADDSH(dtab_ptr, value, name) dtab_add(dtab_ptr, value, DTAB_HASH(DTAB_STRINGIFY(name)))
#define DTAB_ADDH(dtab_ptr, value, name) dtab_add(dtab_ptr, value, DTAB_HASH(name))
#define DTAB_GET(dtab_ptr, name) dtab_get(dtab_ptr, name)
#define DTAB_GETH(dtab_ptr, name) dtab_get(dtab_ptr, DTAB_HASH(name))
#define DTAB_GETSH(dtab_ptr, name) dtab_get(dtab_ptr, DTAB_HASH(DTAB_STRINGIFY(name)))
#define DTAB_DEL(dtab_ptr, name) dtab_del(dtab_ptr, DTAB_HASH(name))
#define DTAB_DELSH(dtab_ptr, name) dtab_del(dtab_ptr, DTAB_HASH(DTAB_STRINGIFY(name)))
#define DTAB_DEL_SCRAMBLE(dtab_ptr, name) dtab_del_scramble(dtab_ptr, DTAB_HASH(name))
#define DTAB_DEL_SCRAMBLESH(dtab_ptr, name) dtab_del_scramble(dtab_ptr, DTAB_HASH(DTAB_STRINGIFY(name)))

#endif /* DTAB */