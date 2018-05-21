#include "types.h"

bolt_object_t *bolt_object_create(char *name) {
    bolt_object_t *object = malloc(sizeof(bolt_object_t));

    object->identifier = hash(name);
    object->name = strdup(name);

    object->property_count = 0;
    object->properties = calloc(MAX_OBJECT_PROPERTIES, sizeof(bolt_object_prop_t));

    return object;
}

void bolt_object_add_property(bolt_object_t *object, char *name, bolt_lang_primitive_type type) {
    bolt_object_prop_t *prop = malloc(sizeof(bolt_object_prop_t));

    prop->identifier = hash(name);
    prop->name = strdup(name);
    prop->type = type;

    object->properties[object->property_count++] = prop;
}

void bolt_object_dispose(bolt_object_t *object) {
    for(int i = 0; i < object->property_count; i++) {
        bolt_object_prop_t *prop = object->properties[i];

        free(prop->name);
        free(prop);
    }

    free(object->name);
    free(object->properties);
    free(object);
}