#ifndef __HTABPRIVATE_H__
#define __HTABPRIVATE_H__
#include "htab.h"
struct htab_item { 
    struct htab_item *next;
    htab_pair_t pair;
};

struct htab{
    size_t size;
    size_t arrSize;
    struct htab_item *array[];
};

static struct htab_item *htab_item_init(htab_key_t key);
#endif
