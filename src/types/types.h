#pragma once

#include "../syntax/lang/lang.h"
#include "../util/hash.h"

#define MAX_OBJECT_PROPERTIES 16 /* for now */

typedef struct bolt_object_prop_s {
    int identifier;
    char *name;
    bolt_lang_primitive_type type;
} bolt_object_prop_t;

typedef struct bolt_object_s {
    int identifier;
    char *name;
    int property_count;
    bolt_object_prop_t **properties;
} bolt_object_t;

bolt_object_t *bolt_object_create(char *name);

void bolt_object_add_property(bolt_object_t *object, char *name, bolt_lang_primitive_type type);

void bolt_object_dispose(bolt_object_t *object);