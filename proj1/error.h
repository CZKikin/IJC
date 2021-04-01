/*
error.h
Autor: Kryštof Sádlík, FIT
Řešení: IJC-DU1, příklad b), 20.3.2020
Přeloženo: gcc (Debian 8.3.0-6) 8.3.0
*/
#ifndef ERRORH
#define ERRORH
#include <stdarg.h>

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif
