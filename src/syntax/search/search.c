#import "search.h"

int bolt_syntax_search_find_keyword(bolt_lang_keyword_type type, bolt_syntax_search_ctx_t *ctx) {
    bolt_lang_t *lang = ctx->parser->lang;

    bolt_lang_keyword_t *keyword = lang->keywords[type];
    int j;

    if (keyword->type != type) {
        return 0;
    }

    for (j = 0; j < keyword->length; j++) {
        if (ctx->parser->source->data[ctx->pos + j] != keyword->keyword[j]) {
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

        if (bolt_syntax_search_find_keyword(BOLT_BLOCK_START, ctx) == 1) {
            in_block++;
        } else if (bolt_syntax_search_find_keyword(BOLT_BLOCK_END, ctx) == 1) {
            in_block--;

            if (in_block == 0) {
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