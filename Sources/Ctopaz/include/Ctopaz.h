#ifndef  CTOPAZ_H
#define  CTOPAZ_H

#include <stdio.h>
#include "alignof.h"
#include "amount.h"
#include "array_size.h"
#include "bech32.h"
#include "bech32_util.h"
#include "bolt11.h"
#include "build_assert.h"
#include "check_type.h"
#include "compiler.h"
#include "config.h"
#include "container_of.h"
#include "cppmagic.h"
#include "endian.h"
#include "hash_u5.h"
#include "hex.h"
#include "likely.h"
#include "list.h"
#include "mem.h"
#include "node_id.h"
#include "overflows.h"
#include "sha256.h"
#include "short_types.h"
#include "str.h"
#include "str_debug.h"
#include "structeq.h"
#include "take.h"
#include "tal.h"
#include "talstr.h"
#include "typesafe_cb.h"
#include "utf8.h"

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