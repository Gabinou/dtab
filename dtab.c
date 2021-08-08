
#include "dtab.h"

/****************************** STRING HASHING *******************************/
uint64_t dtab_hash_djb2(const char * str) {
    /* djb2 hashing algorithm by Dan Bernstein.
    * Description: This algorithm (k=33) was first reported by dan bernstein many
    * years ago in comp.lang.c. Another version of this algorithm (now favored by bernstein)
    * uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; the magic of number 33
    * (why it works better than many other constants, prime or not) has never been adequately explained.
    * [1] https://stackoverflow.com/questions/7666509/hash-function-for-string
    * [2] http://www.cse.yorku.ca/~oz/hash.html */
    uint64_t hash = 5381;
    int32_t str_char;
    while ((str_char = *str++)) {
        hash = ((hash << 5) + hash) + str_char; /* hash * 33 + c */
    }
    return (hash);
}

uint64_t dtab_hash_sdbm(const char * str) {
    /* sdbm hashing algorithm by Dan Bernstein.
    * Description: This algorithm was created for sdbm (a public-domain
    * reimplementation of ndbm) database library. It was found to do
    * well in scrambling bits, causing better distribution of the
    * keys and fewer splits. It also happens to be a good general hashing
    * function with good distribution. The actual function is
    *hash(i) = hash(i - 1) * 65599 + str[i]; what is included below
    * is the faster version used in gawk. [* there is even a faster,
    * duff-device version] the magic constant 65599 was picked out of
    * thin air while experimenting with different constants, and turns
    * out to be a prime. this is one of the algorithms used in
    * berkeley db (see sleepycat) and elsewhere.
    * [1] https://stackoverflow.com/questions/7666509/hash-function-for-string
    * [2] http://www.cse.yorku.ca/~oz/hash.html */
    uint64_t hash = 0;
    uint32_t str_char;
    while ((str_char = *str++)) {
        hash = str_char + (hash << 6) + (hash << 16) - hash;
    }
    return (hash);
}

size_t dtab_found(struct dtab * dtab_ptr, dtab_hash_t in_hash) {
    size_t pos = DTAB_NULL;
    for (size_t i = 0; i < dtab_ptr->num; i++) {
        if (dtab_ptr->keys[i] == in_hash) {
            pos = i;
            break;
        }
    }
    return (pos);
}

void * dtab_get(struct dtab * dtab_ptr, dtab_hash_t in_hash) {
    void * out = NULL;
    size_t pos = dtab_found(dtab_ptr, in_hash);
    if (pos) {
        dtab_byte_t * values_bytesptr = (dtab_byte_t *)(dtab_ptr->values);
        out = (values_bytesptr + (dtab_ptr->bytesize * pos));
    }
    return (out);
}

void dtab_add(struct dtab * dtab_ptr, void * value, dtab_hash_t in_hash) {
    dtab_byte_t * values_bytesptr, *newvalue_bytesptr;
    size_t pos = dtab_found(dtab_ptr, in_hash);
    if (!pos) {
        dtab_ptr->keys[dtab_ptr->num] = in_hash;
        values_bytesptr = (dtab_byte_t *)(dtab_ptr->values);
        newvalue_bytesptr = values_bytesptr + (dtab_ptr->bytesize * dtab_ptr->num);
        dtab_ptr->num++;
    } else {
        values_bytesptr = (dtab_byte_t *)(dtab_ptr->values);
        newvalue_bytesptr = values_bytesptr + (dtab_ptr->bytesize * pos);
    }
    memcpy(newvalue_bytesptr, value, dtab_ptr->bytesize);
    if (dtab_ptr->num == dtab_ptr->len) {
        DTAB_GROW(dtab_ptr);
    }

}

void dtab_del(struct dtab * dtab_ptr, dtab_hash_t in_hash) {
    size_t pos = dtab_found(dtab_ptr, in_hash);
    if ((pos) && (pos < dtab_ptr->num)) {
        memmove(dtab_ptr->keys + pos, dtab_ptr->keys + pos + 1, (dtab_ptr->num - pos - 1)*sizeof(dtab_hash_t)) ;
        dtab_byte_t * values_bytesptr = (dtab_byte_t *)dtab_ptr->values;
        memmove(values_bytesptr + pos * dtab_ptr->bytesize, values_bytesptr + (pos + 1)*dtab_ptr->bytesize, (dtab_ptr->num - pos - 1)*dtab_ptr->bytesize);
        dtab_ptr->num--;
    }

}

void dtab_del_scramble(struct dtab * dtab_ptr, dtab_hash_t in_hash) {
    size_t pos = dtab_found(dtab_ptr, in_hash);
    if ((pos) && (pos < dtab_ptr->num))  {
        memmove(dtab_ptr->keys + pos, dtab_ptr->keys + dtab_ptr->num - 1, sizeof(dtab_hash_t));
        dtab_byte_t * values_bytesptr = (dtab_byte_t *)dtab_ptr->values;
        memmove(values_bytesptr + pos * dtab_ptr->bytesize, values_bytesptr + dtab_ptr->num * dtab_ptr->bytesize, dtab_ptr->bytesize);
        dtab_ptr->num--;
    }
}
