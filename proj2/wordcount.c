#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"

#define WORD_LEN 128

// Velikost pole jsem vybral podle počtu neopakujících se slov ve čtyřech
// scénářích oblíbených filmů. 
// cat lotr1script lotr2script lotr3script pulpFictionScript | ./a.out (z programu wc.cc) | wc -l
// a kvůli dělení jsem našel nejbližší prvočíslo
#define HTAB_SIZE 18121 

void printItOut(htab_pair_t *data){
    printf("%s\t%d\n", data->key, data->value);
}

int main(void)
{   
    FILE *f = stdin;
    
    char *s = malloc(WORD_LEN);
    if(s == NULL){
        fprintf(stderr, "Alloc failed.\n");
        return 1;
    }

    htab_t *tab = htab_init(HTAB_SIZE);
    if(tab == NULL){
        fprintf(stderr, "Alloc failed.\n");
        return 1;
    }
    int wordLength = 0;
    
    while((wordLength = read_word(s, WORD_LEN, f)) != EOF){
        if(wordLength >= WORD_LEN)
            fprintf(stderr, "Word is too long \n");
        
        htab_pair_t *pair = htab_lookup_add(tab, s);
        
        if(pair == NULL){
            fprintf(stderr, "Failed to create a new key pair\n");
            htab_free(tab);
            free(s);
            return 1;
        }

        pair->value++;
    }

    htab_for_each(tab, printItOut);
    return 0;

    #ifdef TEST // Testing htab_move function
        htab_t *newtab = htab_move(5000, tab);
        end = htab_end(newtab);
        for(htab_iterator_t i= htab_begin(newtab); !htab_iterator_equal(i, end); i =    htab_iterator_next(i)) {
            printf("TEST: %s\t%d\n", htab_iterator_get_key(i),  htab_iterator_get_value(i));
        }
        htab_free(newtab);
    #endif
    
    htab_free(tab);
    free(s);
} 
