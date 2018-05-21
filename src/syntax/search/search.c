#include <ctype.h>
#import "search.h"

int bolt_syntax_search_find_keyword(bolt_lang_keyword_type type, bolt_syntax_search_ctx_t *ctx, int index) {
    bolt_lang_t *lang = ctx->parser->lang;

    bolt_lang_keyword_t *keyword = lang->keywords[type];
    int j;

    if (keyword->type != type) {
        return 0;
    }

    for (j = 0; j < keyword->length; j++) {
        if (ctx->parser->source->data[index + j] != keyword->keyword[j]) {
            break;
        }
    }

    if (j >= keyword->length) {
        return j;
    }

    return 0;
}

int bolt_syntax_search_next_block(bolt_syntax_search_ctx_t *ctx, char *buffer) {
    int length = 0;
    int in_block = 0;

    for (int i = ctx->pos; i < (ctx->parser->source->data_length); i++) {
        char c = ctx->parser->source->data[i];

        buffer[length++] = c;

        if (bolt_syntax_search_find_keyword(BOLT_BLOCK_START, ctx, i) == 1) {
            in_block++;
        } else if (bolt_syntax_search_find_keyword(BOLT_BLOCK_END, ctx, i) == 1) {
            in_block--;

            if (in_block <= 0) {
                buffer[length++] = '\0';

                return length;
            }
        }
    }

    return 0;
}

int bolt_syntax_search_until(bolt_syntax_search_ctx_t *ctx, char token, char *buffer) {
    int length = 0;

    for (int i = ctx->pos; i < (ctx->parser->source->data_length); i++) {
        char c = ctx->parser->source->data[i];

        if (c == token) {
            break;
        }

        buffer[length++] = c;
    }

    return length;
}

int bolt_syntax_next_word(int search_length, int start, char *search, char *buffer) {
    int length = 0;

    for(int i = start; i < search_length; i++) {
        char c = search[i];

        if(!isalnum(c)) {
            if(length != 0)
                break;
            else
                continue;
        }

        buffer[length++] = c;
    }

    if(length != 0) {
        buffer[length++] = '\0';
    }

    return length;
}