#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define DEFAULT_LINES 10
#define LONGEST_PATH 4096 /*4096 is the path limit in linux*/
#define LINELIMIT (511 + 1) /* 1 is for the \0 terminator*/

void countAndPrint(FILE *filePtr, long long lineNum){
    char c;
    long long counter = 1;
    while (1){
        c = (filePtr == NULL) ? getchar() : fgetc(filePtr); //později mi došlo že je jsem mohl udělat filePtr = stdin...

        if (c==EOF)
            break;

        if (counter >= lineNum){
            putchar(c);
        }

        if (c=='\n')
            counter++;
    }
}

int main(int argc, char **argv){
    int opt;
    FILE *filePtr = NULL;
    char fromLineMode = 0, fileOpened = 0;
    unsigned long long stackSize = 0;
    char pathToFile[LONGEST_PATH + 1] = {'0'}; 
    if (argc > 4){
        fprintf(stderr, "Usage: ./tail [option] [file]\n");
        return 1;
    }

    while ((opt = getopt(argc, argv, "n:")) != -1){
        switch (opt){
            case 'n':
                if (optarg[0] == '+'){
                    fromLineMode = 1;
                    stackSize = atoll(&(optarg[1]));
                } else {
                    stackSize = atoll(optarg);
                }

                if (stackSize == 0){
                    fprintf(stderr, "Invalid argument after -n\n");
                    return 1;
                }
                break;
            default:
                fprintf(stderr, "Invalid argument or something went really wrong\n");
                return 1;        
        }
    }

    stackSize = (stackSize>0) ? stackSize : DEFAULT_LINES;
    char linesStack[stackSize][LINELIMIT];

    for (unsigned long long i=0; i<stackSize; i++)
        memset(linesStack[i], 0, LINELIMIT);

    if (optind < argc){
        strncpy(pathToFile, argv[optind], LONGEST_PATH);
    }

    if (pathToFile[0] != '0'){
        filePtr = fopen(pathToFile, "r");
        if (filePtr == NULL){
            fprintf(stderr, "Error while opening a file\n");
            return 1; 
        }
        fileOpened = 1;
    }

    if (fromLineMode == 1){
        countAndPrint(filePtr, stackSize);
        if (fileOpened)    fclose(filePtr);
        return 0;
    }

    char buffer[LINELIMIT];
    unsigned long long lineNum = 0;
    char c;
    while (1){
        for (int i=0; (c = (filePtr == NULL) ? getchar() : fgetc(filePtr)) != EOF && c != '\n'; i++){
            if (i==LINELIMIT){
                buffer[i-1] = '\0';
                fprintf(stderr, "Line limit reached, cutting the line");
                break;
            } else {
                buffer[i] = c;
            }
        }

        if (c == EOF)
            break;

        if (lineNum<stackSize){
            strcpy(linesStack[lineNum], buffer);
            lineNum++;
        } else {
            for (unsigned long long i=0; i<lineNum-1; i++)
                strcpy(linesStack[i], linesStack[i+1]);
            strcpy(linesStack[stackSize-1], buffer);
        }
    }
    fclose(filePtr);

    for (unsigned long long i=0; i<lineNum; i++)
        printf("%s\n", linesStack[i]);
    return 0;
}
