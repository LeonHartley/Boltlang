#include <stdio.h>

#include "syntax/lang/lang.h"
#include "syntax/source/source_file.h"
#include "syntax/syntax.h"

int main() {
    bolt_lang_t *lang = bolt_lang_create();

    bolt_lang_add_keyword(lang, "app", BOLT_ENTRY_POINT);
    bolt_lang_add_keyword(lang, "func", BOLT_FUNCTION);
    bolt_lang_add_keyword(lang, "if", BOLT_IF_STATEMENT);
    bolt_lang_add_keyword(lang, "{", BOLT_BLOCK_START);
    bolt_lang_add_keyword(lang, "}", BOLT_BLOCK_END);

    bolt_source_file_t *src = bolt_source_file_create();

    if(bolt_source_file_load("tests/app.bolt", src)) {
        printf("Failed to load source file\n");
        return 1;
    }

    bolt_syntax_parser_t *parser = bolt_parser_create(lang, src);

    if (bolt_parser_build_tree(parser)) {
        // Failed to build tree
        // check parser->errors
        printf("Failed to build syntax tree\n");
        return 1;
    }

   // printf("compiled\n");

    return 0;
}