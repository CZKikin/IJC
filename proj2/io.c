#include "io.h"

int read_word(char *s, int max, FILE *f){
    if(f == NULL){
        fprintf(stderr, "File pointer is invalid\n");
        return -1;
    }

    int c = 0; //because char isn't signed? Idk.. - internet says use int

    while ((c=fgetc(f)) != EOF && isspace(c)); //trim white spaces
    if(c == EOF) return EOF;

    s[0] = c;
    int i = 1;
    for(; i < max - 1; ){
        c = fgetc(f);
        if((isspace(c)) || (c == EOF)) break;
        s[i]=c; 
        i++;
    }
    s[i]='\0';

    if(i == max-1){     //Trimming the rest of the word
        while((c = fgetc(f)) != EOF){
            if(isspace(c)) break;
            i++;
        }
    }
    return i;
}
