#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024
#define LENGTH_OF_INSTRUCTION 4

FILE *fr;
FILE *fm;
FILE *fp;
FILE *fw;
FILE *fs;

int LC;

const char* delimiter_character_col;
const char* delimiter_character_line;
const char* fileread;
const char* fileMOT;
const char* filePOT;
const char* filewrite;
const char* filesymbol;


void write_in_symbol_table(char* line, char* lc) {
    fs = fopen( filesymbol, "a" );
    char *token = (char *)strtok(line, delimiter_character_col);
    fprintf(fs, "%s\t%s\t", token, lc);
    token = (char *)strtok(NULL, delimiter_character_col);
    token = (char *)strtok(NULL, delimiter_character_col);

    if (strlen(token) == 4) {
        fprintf(fs, "%c\n", *(token+2));
    } else if (strlen(token) == 2) {
      fprintf(fs, "%s\n", "-");
    }
    fclose(fs);
}


char* search_symbol_table(char *symbol) {
    fs = fopen( filesymbol, "r" );
    char line[BUFFER];
    char *token_for_col;
    char *token_for_line;
    int flag = 0;
    while (fgets(line, BUFFER, fs)) {
        token_for_line = (char *)strtok(line, delimiter_character_line);
        if (!flag) {
            flag = 1;
            continue;
        }
        char *line_pointer = strdup(line);
        token_for_col = (char *)strtok(line_pointer, delimiter_character_col);
        if ( strcmp(token_for_col, symbol) == 0) {
            token_for_col = (char *)strtok(NULL, delimiter_character_col);
            token_for_col = (char *)strtok(NULL, delimiter_character_col);

            return token_for_col;
        }
    }
}


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
        char str[10];
        sprintf(str, "%d", LC);
        fprintf(fw, "%s\t%s\n", str, token_for_col);
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
    filewrite = "pass1.txt";
    filesymbol = "symbol.txt";
    filePOT = "POT.txt";
    fileMOT = "MOT.txt";

    LC = 0;

    fr = fopen( fileread, "r" );
    fw = fopen( filewrite, "w" );
    fs = fopen( filesymbol, "w" );

    char line[BUFFER];
    char *token_for_column1;
    char *token_for_line;
    int flag = 0;

    while (fgets(line, BUFFER, fr)) {

        token_for_line = (char *)strtok(line, delimiter_character_line);

        if (!flag) {
            fprintf(fs, "%s\t%s\t%s\n", "Symbol", "Location Counter", "Value");
            fclose(fs);
            fprintf(fw, "%s\t%s\n", "Relative Address", "Instruction");
            flag = 1;
            continue;
        }

        char *line_pointer_for_first_column = strdup(line);
        token_for_column1 = (char *)strtok(line_pointer_for_first_column, delimiter_character_col);

        char *line_pointer_for_third_column = strdup(line);
        char *line_pointer_for_symbol_table = strdup(line);

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

                        write_in_symbol_table(line_pointer_for_symbol_table, str);

                        char *token_for_column3 = (char *)strtok(line_pointer_for_third_column, delimiter_character_col);
                        char *value = search_symbol_table(token_for_column3);
                        fprintf(fw, "%s\t%s\n", str, value);

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
