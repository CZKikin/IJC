#include "htab.h"
#include "htabPrivate.h"
#include <stdlib.h>
#include <stdint.h>

htab_t *htab_init(size_t n){
    htab_t *tab = malloc(sizeof(htab_t) + n * sizeof(struct htab_item_t *));
    if(tab == NULL) return NULL;
    for(size_t i = 0; i < n; i++){
        tab->array[i] = NULL;
    }
    tab->size = 0; 
    tab->arrSize = n; 
    return tab;
}

size_t htab_hash_function(htab_key_t str){
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}

static struct htab_item *htab_item_init(htab_key_t key){
    struct htab_item *itemPtr = malloc(sizeof(struct htab_item));
    if(itemPtr == NULL) return NULL;
    
    size_t keyLen = strlen(key)+1;
    itemPtr->pair.key = malloc(keyLen);
    memcpy((char*)itemPtr->pair.key, key, keyLen);
    itemPtr->next = NULL;
    itemPtr->pair.value = 0;
    return itemPtr;
}

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)){
    for (size_t i=0; i < t->arrSize; i++){
        if (t->array[i] == NULL) continue;
        f(&t->array[i]->pair);
    }
}

bool htab_erase(htab_t *t, htab_key_t key){
    size_t hash = htab_hash_function(key);
    size_t index = hash % t->arrSize;
    struct htab_item *itemPtr = t->array[index];

    if (itemPtr == NULL) return false;
    free((char *)itemPtr->pair.key);
    free(itemPtr);
    t->array[index] = NULL;
    return true;
}

void htab_clear(htab_t *t){
    for (size_t i=0; i < t->arrSize; i++){
        if (t->array[i] == NULL) continue;
        free((char *)t->array[i]->pair.key);
        free((htab_pair_t *)t->array[i]);
        t->array[i] = NULL;
    }
}

void htab_free(htab_t *t){
    htab_clear(t);
    free(t);
    t=NULL;
}

htab_pair_t *htab_lookup_add(htab_t *t, const char *key){
    size_t hash = htab_hash_function(key);
    size_t index = hash % t->arrSize;
    struct htab_item *itemPtr = t->array[index];
    if(itemPtr == NULL){ /* Nic tam není, přidej */
        itemPtr = htab_item_init(key);
        if(itemPtr == NULL) return NULL;

        t->size++;
        t->array[index] = itemPtr;
    }
    return &itemPtr->pair;
}

htab_t *htab_move(size_t n, htab_t *from){
    htab_t *newTab = htab_init(n);
    if(newTab == NULL) return NULL;

    for(size_t i=0; i < from->arrSize; i++) {
        if (from->array[i] == NULL) continue;
        if(htab_lookup_add(newTab, from->array[i]->pair.key) == NULL) return NULL;
    }

    newTab->arrSize = n;
    newTab->size = from->size;

    htab_clear(from);

    return newTab;
}

htab_pair_t *htab_find(htab_t *t, htab_key_t key){
    size_t hash = htab_hash_function(key);
    size_t index = hash % t->arrSize;
    struct htab_item *itemPtr = t->array[index];
    if(itemPtr == NULL) return NULL;
    return &itemPtr->pair;
}

size_t htab_size(const htab_t *t){
    return t->size;
}

size_t htab_bucket_count(const htab_t *t){
    return t->arrSize;
}
