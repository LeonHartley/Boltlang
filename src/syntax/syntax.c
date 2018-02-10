#include "syntax.h"

#include "search/search.h"

bolt_syntax_parser_t *bolt_parser_create(bolt_lang_t *lang, bolt_source_file_t *source_file) {
    bolt_syntax_parser_t *parser = (bolt_syntax_parser_t *) malloc(sizeof(bolt_syntax_parser_t));

    parser->source = source_file;
    parser->lang = lang;
    parser->tree = malloc(sizeof(bolt_syntax_tree_t));

    return parser;
}

int bolt_parser_function(bolt_syntax_search_ctx_t *ctx, char *buffer) {
    int func_name_len = bolt_syntax_search_until(ctx, '(', buffer);
    char *func_name = malloc((size_t) (func_name_len + 1));

    memcpy(func_name, buffer, (size_t) func_name_len);

    func_name[func_name_len] = '\0';

    printf("function loaded: %s\n", func_name);

    return func_name_len + 1;
}

int bolt_parser_object(bolt_syntax_search_ctx_t *ctx, char *buffer) {
    int obj_name_len = bolt_syntax_search_until(ctx, ' ', buffer);
    char *obj_name = malloc((size_t) (obj_name_len + 1));

    memcpy(obj_name, buffer, (size_t) obj_name_len);

    obj_name[obj_name_len] = '\0';

    printf("object loaded: %s\n", obj_name);
    return obj_name_len + 1;
}

int bolt_parser_module_name(bolt_syntax_search_ctx_t *ctx,char *buffer) {
    int module_name_len = bolt_syntax_search_until(ctx, ';', buffer);

    ctx->parser->tree->module_name = malloc((size_t) (module_name_len + 1));
    memcpy(ctx->parser->tree->module_name, buffer, (size_t) module_name_len);

    ctx->parser->tree->module_name[module_name_len] = '\0';

    printf("module loaded: %s\n", ctx->parser->tree->module_name);

    return module_name_len + 1;
}

int bolt_parser_build_tree(bolt_syntax_parser_t *parser) {
    bolt_syntax_search_ctx_t ctx = {
            .mode = BOLT_MODE_FUNCTIONS,
            .parser = parser,
            .pos = 0
    };

    char script_buffer[parser->source->data_length];

    while (ctx.pos < parser->source->data_length) {
        int token = 0;

        if (parser->tree->module_name == NULL && (token = bolt_syntax_search_find_keyword(BOLT_MODULE_NAME, &ctx))) {
            ctx.pos += token + 1;

            ctx.pos += bolt_parser_module_name(&ctx, script_buffer);
        } else if (parser->source->data[ctx.pos] != ' ') {
            if ((token = bolt_syntax_search_find_keyword(BOLT_OBJECT, &ctx))) {
                ctx.pos += token + 1;

                ctx.pos += bolt_parser_object(&ctx, script_buffer);
            } else if ((token = bolt_syntax_search_find_keyword(BOLT_FUNCTION, &ctx))) {
                ctx.pos += token + 1;

                ctx.pos += bolt_parser_function(&ctx, script_buffer);
            }
        }

        ctx.pos++;
    }

    return 0;
}

void bolt_parser_dispose(bolt_syntax_parser_t *parser) {
    free(parser);
}