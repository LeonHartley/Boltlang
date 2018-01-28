#pragma once

#include "source/source_file.h"
#include "lang/lang.h"

#define SEARCH_MODE_BLOCK 1

typedef struct bolt_syntax_tree_s {
	void *entryPoint;
} bolt_syntax_tree_t;

typedef struct bolt_syntax_parser_s {
	bolt_source_file_t *source;
	bolt_syntax_tree_t *tree;

    bolt_lang_t *lang;
} bolt_syntax_parser_t;

bolt_syntax_parser_t *bolt_parser_create(bolt_lang_t *lang, bolt_source_file_t *source_file);

int bolt_parser_build_tree(bolt_syntax_parser_t *parser);

void bolt_parser_dispose(bolt_syntax_parser_t *parser);