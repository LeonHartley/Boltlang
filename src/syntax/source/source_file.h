#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct bolt_source_file_s {
	const char *name;
	char *data;
	long data_length;
} bolt_source_file_t;

bolt_source_file_t *bolt_source_file_create();

int bolt_source_file_load(const char *file_loc, bolt_source_file_t *file);

void bolt_source_file_dispose(bolt_source_file_t *file);