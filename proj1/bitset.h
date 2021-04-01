/*
bitset.h
Autor: Kryštof Sádlík, FIT
Řešení: IJC-DU1, příklad a), 21.3.2021
Přeloženo: gcc (Debian 8.3.0-6) 8.3.0
*/
#ifndef BITSETH
#define BITSETH
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "error.h"

typedef unsigned long bitset_t[];

typedef unsigned long bitset_index_t;

#define UL_IN_BITS (sizeof(unsigned long) * CHAR_BIT)

#define bitset_create(name, size) static_assert((size) > 0, "Cannot create this field");\
    unsigned long (name)[((size) / UL_IN_BITS) + ((size) % UL_IN_BITS ? 1 : 0) + 1] = {(size)};

#define bitset_alloc(name, size) assert((size) > 0 && "Cannot create this field");\
    unsigned long *(name) = calloc(0, (((size)/UL_IN_BITS) + ((size) % UL_IN_BITS ? 1:0) + 1)) ;\
    assert(((name) != NULL) && "error in memory allocation");\
    (name)[0] = (size);

#define bitset_free(name) free((name));\
    (name) = NULL;

#ifdef USE_INLINE
    static inline unsigned long bitset_size(bitset_t name){
        return name[0];
    }

    static inline unsigned long bitset_getbit(bitset_t name, const bitset_index_t index){
        if((index >= bitset_size(name))) error_exit("bitset_getbit: Index %lu out of boundaries 0..%lu", (unsigned long)index, (unsigned long)(name[0]-1));

        return ((name[((index)/UL_IN_BITS) + 1] & (1UL << ((index)%UL_IN_BITS))) != 0);
    }

    static inline void bitset_setbit(bitset_t name, const bitset_index_t index, const int expr){
        if((index >= bitset_size(name))) error_exit("bitset_setbit: Index %lu out of boundaries 0..%lu", (unsigned long)index, (unsigned long)(name[0]-1));
        
        (expr != 0) ? (name[(index)/UL_IN_BITS + 1] |=  (1UL << ((index)%UL_IN_BITS))) : 
                       (name[(index)/UL_IN_BITS + 1] &= ~(1UL << ((index)%UL_IN_BITS)));
        return;
    }
#else 
    #define bitset_size(name) name[0]

    #define bitset_setbit(name, index, expr)\
        if((unsigned long)(index) >= (unsigned long) bitset_size((name)))\
            error_exit("bitset_setbit: Index %lu is out of boundaries 0..%lu", (unsigned long)index, (unsigned long)(name[0]-1));\
        else\
            (expr != 0) ? (name[(index)/UL_IN_BITS + 1] |=  (1UL << ((index)%UL_IN_BITS))) :\
                     (name[(index)/UL_IN_BITS + 1] &= ~(1UL << ((index)%UL_IN_BITS)));

    #define bitset_getbit(name, index) (index >= bitset_size(name)) ?                                                                                 \
        (error_exit("bitset_getbit: Index %lu is out of boundaries 0..%lu", (unsigned long)index, (unsigned long)(name[0]-1)), -1) :         \
        ((name[((index)/UL_IN_BITS) + 1] & (1UL << ((index)%UL_IN_BITS))) != 0)
#endif 
#endif /* BITSETH */
