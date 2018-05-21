#include "lang.h"
#include "../syntax.h"
#include "../../util/hash.h"

bolt_lang_t *bolt_lang_create() {
    bolt_lang_t *lang = (bolt_lang_t *) malloc(sizeof(bolt_lang_t));

    lang->keywords_count = 0;
    lang->keywords = calloc(MAX_KEYWORDS, sizeof(bolt_lang_keyword_t));

    lang->primitives_count = 0;
    lang->primitives = calloc(MAX_PRIMITIVES, sizeof(bolt_lang_primitive_t));

    return lang;
}

void bolt_lang_dispose(bolt_lang_t *lang) {
    for(int i = 0; i < lang->keywords_count; i++) {
        free(lang->keywords[i]);
    }

    for(int i = 0; i < lang->primitives_count; i++) {
        free(lang->primitives[i]);
    }

    free(lang->keywords);
    free(lang->primitives);

    free(lang);
}

void bolt_lang_add_keyword(bolt_lang_t *lang, char *keyword_str, bolt_lang_keyword_type type) {
    bolt_lang_keyword_t *keyword = (bolt_lang_keyword_t *) malloc(sizeof(bolt_lang_keyword_t));

    keyword->keyword = keyword_str;
    keyword->length = strlen(keyword_str);
    keyword->type = type;

    lang->keywords_count++;
    lang->keywords[type] = keyword;
}

void bolt_lang_add_primitive(bolt_lang_t *lang, char *identifier, bolt_lang_primitive_type type) {
    bolt_lang_primitive_t *primitive = (bolt_lang_primitive_t *) malloc(sizeof(bolt_lang_primitive_t));

    primitive->identifier = hash(identifier);
    primitive->type = type;

    lang->primitives_count++;
    lang->primitives[type] = primitive;
}

bolt_lang_primitive_type bolt_lang_get_primitive(bolt_lang_t *lang, int identifier) {
    for(int i = 0; i < lang->primitives_count; i++) {
        if(lang->primitives[i]->identifier == identifier) {
            return lang->primitives[i]->type;
        }
    }
}