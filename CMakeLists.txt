cmake_minimum_required(VERSION 3.9)
project(Boltlang C)

add_executable(Boltlang
		src/main.c
        src/syntax/lang/lang.h
        src/syntax/source/source_file.h
        src/syntax/syntax.h
        src/syntax/lang/lang.c
        src/syntax/syntax.c
        src/syntax/source/source_file.c
        src/syntax/search/search.c
        src/syntax/search/search.h
        src/util/map.c
        src/util/map.h
        src/types/functions.c
        src/types/functions.h
		src/types/types.h
        src/util/hash.c
        src/util/hash.h
		src/exec/tree.c
		src/exec/tree.h
		src/exec/context.c
		src/exec/context.h src/syntax/parsers/object.c src/syntax/parsers/object.h src/types/types.c)