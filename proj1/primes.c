/*
primes.c
Autor: Kryštof Sádlík, FIT
Řešení: IJC-DU1, příklad a), 20.3.2020
Přeloženo: gcc (Debian 8.3.0-6) 8.3.0
*/
#include "bitset.h"
#include "eratosthenes.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define fieldSize (200000000)
int main(){
    clock_t start = clock();
    bitset_create(mainField, fieldSize);

    Eratosthenes(mainField);

    for (unsigned long i = fieldSize-1, j = 0; j < 10; --i){
        if (bitset_getbit(mainField, i) == 0){ 
            printf("%lu\n", i);
            j++;
        }
    }
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
