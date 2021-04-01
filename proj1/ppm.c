/*
ppm.c
Autor: Kryštof Sádlík, FIT
Řešení: IJC-DU1, příklad b), 20.3.2020
Přeloženo: gcc (Debian 8.3.0-6) 8.3.0
*/
#include "ppm.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ppm_free(struct ppm *p){
    free(p);
}

struct ppm * ppm_read(const char *filename){
    FILE *fileHandle;

    if((fileHandle = fopen(filename, "rw")) == NULL){
        warning_msg("Failed to open file: %s.\n", filename);
        return NULL;
    }

    unsigned int xsize;
    unsigned int ysize;
    char fileType[3];
    unsigned char color;

    if(fscanf(fileHandle, "%2s %u %u %hhu", fileType, &xsize, &ysize, &color) < 4 ){
        warning_msg("Failed to read header.\n");
        fclose(fileHandle);
        return NULL;
    }

    if(strcmp(fileType, "P6")) {
        warning_msg("Bad file format.\n");
        fclose(fileHandle);
        return NULL;
    }

    size_t ppmDataSize = (3* xsize * ysize);

    if(ppmDataSize > PPM_SIZE_LIMIT){
        warning_msg("File is too big!\n");
        fclose(fileHandle);
        return NULL;
    }

    struct ppm *ppm_ptr = malloc(sizeof(struct ppm) + ppmDataSize);
    if (ppm_ptr == NULL) {
        warning_msg("Alloc failed.\n");
        fclose(fileHandle);
        return NULL;
    }

    ppm_ptr->xsize=xsize;
    ppm_ptr->ysize=ysize;

    if(fread(ppm_ptr->data, sizeof(char), ppmDataSize, fileHandle) != ppmDataSize){
        warning_msg("Failed to load data.\n", filename);
        fclose(fileHandle);
        free(ppm_ptr);
        return NULL;
    }

    fclose(fileHandle);
    return ppm_ptr;
}
