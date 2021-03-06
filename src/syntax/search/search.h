#pragma once

#include "../syntax.h"

typedef enum bolt_syntax_search_mode_e {
    BOLT_MODE_FUNCTIONS = 0,
    BOLT_MODE_BLOCK = 1
} bolt_syntax_search_mode;

typedef struct bolt_syntax_search_ctx_s {
    bolt_syntax_parser_t *parser;
    bolt_syntax_search_mode mode;

    int pos;
} bolt_syntax_search_ctx_t;

int bolt_syntax_search_find_keyword(bolt_lang_keyword_type type, bolt_syntax_search_ctx_t *ctx, int index);

int bolt_syntax_search_next_block(bolt_syntax_search_ctx_t *ctx, char *buffer);

int bolt_syntax_search_until(bolt_syntax_search_ctx_t *ctx, char token, char *buffer);

int bolt_syntax_next_word(int search_length, int index, char *search, char *buffer);