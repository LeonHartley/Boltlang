#include <stdio.h>
#include <ctype.h>
#include "object.h"
#include "../search/search.h"

bolt_object_t *bolt_object_parser(bolt_lang_t *lang, char *name, int block_length, char *block) {
    bolt_object_t *object = bolt_object_create(name);
    char buffer[256];

    int index = 0;

    while (block[index++] != lang->keywords[BOLT_BLOCK_END]->keyword[0]) {
        if (!isalnum(block[index])) {
            continue;
        }

        int prop_name_len = bolt_syntax_next_word(block_length, index, block, buffer);
        index += (prop_name_len - 1);

        char prop_name[prop_name_len];
        memcpy(prop_name, buffer, (size_t) prop_name_len);

        int prop_type_len = bolt_syntax_next_word(block_length, index, block, buffer);
        index += (prop_type_len - 1);

        char prop_type[prop_type_len];
        memcpy(prop_type, buffer, (size_t) prop_type_len);

        bolt_object_add_property(object, prop_name, bolt_lang_get_primitive(lang, hash(prop_type)));
    }

    for (int i = 0; i < object->property_count; i++) {
        bolt_object_prop_t *prop = object->properties[i];
        printf("object prop: %s type: %i\n", prop->name, prop->type);

        // now can do stuff like this:
        switch (prop->type) {
            case BOLT_STRING:
                printf("type %s is string!\n", prop->name);
                break;
        }
    }
}