#pragma once

typedef enum bolt_primitive_type_e {
    BOLT_STRING = 0,
    BOLT_INT
} bolt_primitive_type;

bolt_primitive_type bolt_get_type(char *hash) {
    return BOLT_STRING;
}