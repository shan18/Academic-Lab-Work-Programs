/* This file creates the symbol table
 * required by the assembler to read
 * the object code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024
#define LENGTH_OF_INSTRUCTION 4

FILE *fr;
FILE *fm;
FILE *fp;
FILE *fw;

int LC;

const char* delimiter_character_col;
const char* delimiter_character_line;
const char* fileread;
const char* fileMOT;
const char* filePOT;
const char* filewrite;


int find_in_MOT(char *ins) {
    fm = fopen( fileMOT, "r" );
    if (fm == NULL) {
        puts("Cannot open file fm.");
        fclose(fr);
        fclose(fw);
        exit(1);
    }
    char line[BUFFER];
    char *token_for_col;
    char *token_for_line;
    int flag = 0;
    int found = 0;
    while (fgets(line, BUFFER, fm)) {
        token_for_line = (char *)strtok(line, delimiter_character_line);
        if (!flag) {
            flag = 1;
            continue;
        }
        char *line_pointer = strdup(line);
        token_for_col = (char *)strtok(line_pointer, delimiter_character_col);
        if ( strcmp(token_for_col, ins) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        token_for_col = (char *)strtok(NULL, delimiter_character_col);
        LC += atof(token_for_col);
    }

    fclose(fm);
    return found;
}


int find_in_POT(char *ins) {
    fp = fopen( filePOT, "r" );
    if (fp == NULL) {
        puts("Cannot open file fp.");
        fclose(fr);
        fclose(fw);
        exit(1);
    }
    char line[BUFFER];
    char *token_for_line;
    int found = 0;

    while (fgets(line, BUFFER, fp)) {
        token_for_line = (char *)strtok(line, delimiter_character_line);
        char *line_pointer = strdup(line);
        if ( strcmp(token_for_line, ins) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}


int main() {

    delimiter_character_col = "\t";
    delimiter_character_line = "\n";
    fileread = "instructions.txt";
    filewrite = "symbol.txt";
    filePOT = "POT.txt";
    fileMOT = "MOT.txt";

    LC = 0;

    fr = fopen( fileread, "r" );
    fw = fopen( filewrite, "w" );

    char line[BUFFER];
    char *token_for_column1;
    char *token_for_line;
    int flag = 0;

    while (fgets(line, BUFFER, fr)) {

        token_for_line = (char *)strtok(line, delimiter_character_line);

        if (!flag) {
            fprintf(fw, "%s\t%s\t%s\n", "Symbol", "Location Counter", "Value");
            flag = 1;
            continue;
        }

        char *line_pointer_for_first_column = strdup(line);
        token_for_column1 = (char *)strtok(line_pointer_for_first_column, delimiter_character_col);

        char *line_pointer_for_third_column = strdup(line);

        while ( token_for_column1 != NULL ) {

            if( strcmp(token_for_column1, "#") != 0 ) {
                if ( find_in_MOT(token_for_column1) || !strcmp(token_for_column1, "USING") || !strcmp(token_for_column1, "START") || !strcmp(token_for_column1, "END")) {
                    break;
                }
                else {

                    char *token_for_column2 = (char *)strtok(token_for_line, delimiter_character_col);
                    token_for_column2 = (char *)strtok(NULL, delimiter_character_col);

                    if ( find_in_POT(token_for_column2) ) {

                        char str[10];
                        sprintf(str, "%d", LC);

                        char *token_for_column3 = (char *)strtok(line_pointer_for_third_column, delimiter_character_col);
                        fprintf(fw, "%s\t%s\t", token_for_column3, str);
                        token_for_column3 = (char *)strtok(NULL, delimiter_character_col);
                        token_for_column3 = (char *)strtok(NULL, delimiter_character_col);

                        if (strlen(token_for_column3) == 4) {
    	                    fprintf(fw, "%c\n", *(token_for_column3+2));
                        } else if (strlen(token_for_column3) == 2) {
                          fprintf(fw, "%s\n", "-");
                        }

                        LC += LENGTH_OF_INSTRUCTION;
                	}
                }
            }
            token_for_column1 = (char *)strtok(NULL, delimiter_character_col);

        }
    }

    fclose(fr);
    fclose(fw);
}
