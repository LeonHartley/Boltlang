#pragma once

#include <stdlib.h>
#include <string.h>

#define MAX_KEYWORDS 10

typedef enum bolt_lang_keyword_type_e {
    BOLT_MODULE_NAME = 0,
    BOLT_ENTRY_POINT,
    BOLT_FUNCTION,
    BOLT_IF_STATEMENT,
    BOLT_BLOCK_START,
    BOLT_BLOCK_END,
    BOLT_OBJECT
} bolt_lang_keyword_type;

typedef struct bolt_lang_keyword_s {
    bolt_lang_keyword_type type;

    size_t length;
    char *keyword;
} bolt_lang_keyword_t;

typedef struct bolt_lang_s {
    int keywords_count;
    bolt_lang_keyword_t **keywords;
} bolt_lang_t;

bolt_lang_t *bolt_lang_create();

void bolt_lang_dispose(bolt_lang_t *lang);

void bolt_lang_add_keyword(bolt_lang_t *lang, char *keyword_str, bolt_lang_keyword_type type);