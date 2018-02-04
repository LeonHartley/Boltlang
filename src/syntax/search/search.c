#import "search.h"

int bolt_syntax_search_find_keyword(bolt_lang_keyword_type type, bolt_syntax_search_ctx_t *ctx) {
    bolt_lang_t *lang = ctx->parser->lang;

    for (int i = 0; i < lang->keywords_count; i++) {
        bolt_lang_keyword_t *keyword = lang->keywords[i];
        int j;

        if (keyword->type != type) {
            continue;
        }

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

int bolt_syntax_search_next_block(bolt_syntax_search_ctx_t *ctx, char *buffer) {
    int length = 0;

    int in_block = 0;

    for (int i = ctx->pos; i < (ctx->parser->source->data_length); i++) {
        char c = ctx->parser->source->data[i];

        buffer[length++] = c;

        if (c == '{') {
            in_block++;
        } else if (c == '}') {
            in_block--;

            if (in_block == 0) {
                buffer[length++] = '\0';

                return length;
            }
        }
    }

    return 0;
}