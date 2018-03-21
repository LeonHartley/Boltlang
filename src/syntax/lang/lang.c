#include "lang.h"
#include "../syntax.h"

bolt_lang_t *bolt_lang_create() {
    bolt_lang_t *lang = (bolt_lang_t *) malloc(sizeof(bolt_lang_t));

    lang->keywords_count = 0;
    lang->keywords = calloc(MAX_KEYWORDS, sizeof(bolt_lang_keyword_t));

    return lang;
}

void bolt_lang_dispose(bolt_lang_t *lang) {
    for(int i = 0; i < lang->keywords_count; i++) {
        free(lang->keywords[i]);
    }

    free(lang->keywords);
    free(lang);
}

void bolt_lang_add_keyword(bolt_lang_t *lang, char *keyword_str, bolt_lang_keyword_type type) {
    bolt_lang_keyword_t *keyword = (bolt_lang_keyword_t *) malloc(sizeof(bolt_lang_keyword_t));

    keyword->keyword = keyword_str;
    keyword->length = strlen(keyword_str);
    keyword->type = type;

    lang->keywords[type] = keyword;
}