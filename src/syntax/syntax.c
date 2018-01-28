#include "syntax.h"

#include "search/search.h"

bolt_syntax_parser_t *bolt_parser_create(bolt_lang_t *lang, bolt_source_file_t *source_file) {
    bolt_syntax_parser_t *parser = (bolt_syntax_parser_t *) malloc(sizeof(bolt_syntax_parser_t));

    parser->source = source_file;
    parser->lang = lang;

    return parser;
}

int bolt_parser_build_tree(bolt_syntax_parser_t *parser) {
    bolt_syntax_search_ctx_t ctx = {
            .mode = BOLT_MODE_FUNCTIONS,
            .parser = parser,
            .pos = 0
    };

    size_t func_buffer_pos;
    char function_buffer[1024];

    while (ctx.pos < parser->source->data_length) {
        int token = 0;

        if ((token = bolt_syntax_search_find_keyword(BOLT_FUNCTION, &ctx)) == 4) {
            func_buffer_pos = 0;

            ctx.mode = BOLT_MODE_BLOCK; // we're now searching for the name & then a full block of code like: { ... }
            ctx.pos += token + 1;

            char c = parser->source->data[ctx.pos];

            char *func_name;

            while ((c != '(')) {
                function_buffer[func_buffer_pos] = c;

                c = parser->source->data[(ctx.pos + 1) + func_buffer_pos++];
            }

            func_name = malloc(func_buffer_pos + 1);

            // Now we need to get the name of the function.
            memcpy(func_name, function_buffer, func_buffer_pos);
            func_name[func_buffer_pos] = '\0';

            printf("function loaded: %s\n", func_name);

            free(func_name);
        }

        ctx.pos++;
    }

    return 0;
}

void bolt_parser_dispose(bolt_syntax_parser_t *parser) {
    free(parser);
}