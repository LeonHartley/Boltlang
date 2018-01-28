#include "source_file.h"

bolt_source_file_t *bolt_source_file_create() {
    return (bolt_source_file_t *)malloc(sizeof(bolt_source_file_t));
}

int bolt_source_file_load(const char *file_loc, bolt_source_file_t *file) {
    int size = 0;

    FILE *f = fopen(file_loc, "rt");

    if (f == NULL) {
        return 1;
    }

    fseek(f, 0, SEEK_END);
    size_t length = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);

    buffer[length] = '\0';
    fread(buffer, 1, length, f);

    fclose(f);

    file->data_length = length;
    file->name = file_loc;
    file->data = buffer;

    return 0;
}

void bolt_source_file_dispose(bolt_source_file_t *file) {
    if (file->data_length) {
        free(file->data);
    }

    free(file);
}