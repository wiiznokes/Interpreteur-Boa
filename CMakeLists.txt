cmake_minimum_required(VERSION 3.24)
project(Projet_interpreteur C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(Projet_interpreteur
        src/analyse_lexical.c
        src/analyse_lexical.h
        src/analyse_syntaxique.c
        src/analyse_syntaxique.h
        src/ast_construction.c
        src/ast_construction.h
        src/ast_parcours.c
        src/ast_parcours.h
        src/essai_ast.c
        src/lecture_caracteres.c
        src/lecture_caracteres.h)
