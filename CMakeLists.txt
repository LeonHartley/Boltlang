cmake_minimum_required(VERSION 3.9)
project(Boltlang C)

set(CMAKE_C_STANDARD 11)

add_executable(Boltlang
        src/main.c
        src/syntax/lang/lang.h
        src/syntax/source/source_file.h
        src/syntax/syntax.h src/syntax/lang/lang.c src/syntax/syntax.c src/syntax/source/source_file.c src/syntax/search/search.c src/syntax/search/search.h)