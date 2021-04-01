/*
error.c
Autor: Kryštof Sádlík, FIT
Řešení: IJC-DU1, příklad b), 20.3.2020
Přeloženo: gcc (Debian 8.3.0-6) 8.3.0
*/
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args); 
    va_end(args);
}

void error_exit(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, fmt, args); 
    va_end(args);
    exit(1);
}
