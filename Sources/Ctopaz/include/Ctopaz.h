#ifndef  CTOPAZ_H
#define  CTOPAZ_H

#include "hex.h"
#include <stdio.h>

#define  MAX_BLOCKS 1024

enum block_type {
    BLOCK_HASHTAG = 1,
    BLOCK_TEXT = 2,
    BLOCK_MENTION = 3,
    BLOCK_URL = 4,
    BLOCK_INVOICE = 5,
};

typedef struct str_block {
    const char *start;
    const char *end;
} str_block_t;

typedef struct invoice_block {
    struct str_block invstr;
    union {
        struct bolt11 *bolt11;
    };
} invoice_block_t;

typedef struct block {
    enum block_type type;
    union {
        struct str_block str;
        struct invoice_block invoice;
        int mention;
    } block;
} block_t;

typedef struct blocks {
    int num_blocks;
    struct block *blocks;
} blocks_t;

void blocks_init(struct blocks *blocks);
void blocks_free(struct blocks *blocks);
int damus_parse_content(struct blocks *blocks, const char *content);

#endif