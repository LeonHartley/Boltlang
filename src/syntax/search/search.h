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

    int block_start_ctr;
    int block_end_ctr;
} bolt_syntax_search_ctx_t;

int bolt_syntax_search_find_keyword(bolt_lang_keyword_type type, bolt_syntax_search_ctx_t *ctx) {
    bolt_lang_t *lang = ctx->parser->lang;

    for (int i = 0; i < lang->keywords_count; i++) {
        bolt_lang_keyword_t *keyword = lang->keywords[i];
        int j;

        for (j = 0; j < keyword->length; j++) {
            if (ctx->parser->source->data[ctx->pos + j] != keyword->keyword[j]) {
                break;
            }
        }

        if (j >= keyword->length) {
            return j;
        }
    }

    return 0;
}