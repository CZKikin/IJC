/*
ppm.h
Autor: Kryštof Sádlík, FIT
Řešení: IJC-DU1, příklad b), 20.3.2020
Přeloženo: gcc (Debian 8.3.0-6) 8.3.0
*/
#ifndef PPMH
#define PPMH

#define PPM_SIZE_LIMIT (8000 * 8000 * 3)

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    
};

struct ppm *ppm_read(const char * filename);
void ppm_free(struct ppm *p);
#endif
