#include <stdio.h>
#include <time.h>

#include "syntax/lang/lang.h"
#include "syntax/source/source_file.h"
#include "syntax/syntax.h"
#include "util/hash.h"

int main() {
    clock_t start = clock(), diff;

    bolt_lang_t *lang = bolt_lang_create();

    bolt_lang_add_keyword(lang, "module", BOLT_MODULE_NAME);
    bolt_lang_add_keyword(lang, "app", BOLT_ENTRY_POINT);
    bolt_lang_add_keyword(lang, "obj", BOLT_OBJECT);
    bolt_lang_add_keyword(lang, "func", BOLT_FUNCTION);
    bolt_lang_add_keyword(lang, "if", BOLT_IF_STATEMENT);
    bolt_lang_add_keyword(lang, "{", BOLT_BLOCK_START);
    bolt_lang_add_keyword(lang, "}", BOLT_BLOCK_END);

    bolt_lang_add_primitive(lang, "int", BOLT_INT);
    bolt_lang_add_primitive(lang, "string", BOLT_STRING);
    bolt_lang_add_primitive(lang, "long", BOLT_LONG);
    bolt_lang_add_primitive(lang, "bool", BOLT_BOOL);
    bolt_lang_add_primitive(lang, "byte", BOLT_BYTE);

    bolt_source_file_t *src = bolt_source_file_create();

    if (bolt_source_file_load("tests/app.bolt", src)) {
        printf("Failed to load source file\n");
        return 1;
    }

    bolt_syntax_parser_t *parser = bolt_parser_create(lang, src);

    if (bolt_parser_parse_script(parser)) {
        // Failed to build tree
        // check parser->errors
        printf("Failed to build syntax tree\n");
        return 1;
    }

    diff = clock() - start;


    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

    return 0;
}