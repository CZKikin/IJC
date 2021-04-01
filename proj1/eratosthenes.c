/*
eratosthenes.c
Autor: Kryštof Sádlík, FIT
Řešení: IJC-DU1, příklad a), 20.3.2020
Přeloženo: gcc (Debian 8.3.0-6) 8.3.0
*/
#include "eratosthenes.h"
#include "bitset.h"
#include <math.h>

void Eratosthenes(bitset_t mainField){
    unsigned long i, j, size = bitset_size(mainField);
    
    for (i = 2; i < sqrt(size); ++i){
        if (bitset_getbit(mainField, i) == 0){
            for(j = i << 1; j < size; j += i)
                bitset_setbit(mainField, j, 1);
        }
    }
}
