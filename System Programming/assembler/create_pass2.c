#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024

FILE *fr;
FILE *fm;
FILE *fp;
FILE *fw;
FILE *fs;

const char* delimiter_character_col;
const char* delimiter_character_line;
const char* fileread;
const char* fileMOT;
const char* filewrite;
const char* filesymbol;

char *temp_literal;
char *temp_symbol;


int find_in_MOT(char *ins) {
    fm = fopen( fileMOT, "r" );

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
        //printf("%s\n", token_for_col);
        token_for_col = (char *)strtok(NULL, delimiter_character_col);
        //printf("%s\n", token_for_col);
        temp_literal = token_for_col;
    }

    fclose(fm);
    return found;
}


void find_in_symbol_table(char *ins) {
	fs = fopen( filesymbol, "r" );

    char line[BUFFER];
    char *token_for_col;
    char *token_for_line;
    int flag = 0;
    int found = 0;

    while (fgets(line, BUFFER, fs)) {
        token_for_line = (char *)strtok(line, delimiter_character_line);
        if (!flag) {
            flag = 1;
            continue;
        }

        token_for_col = (char *)strtok(token_for_line, delimiter_character_col);
        if ( strcmp(token_for_col, ins) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        token_for_col = (char *)strtok(NULL, delimiter_character_col);
        token_for_col = (char *)strtok(NULL, delimiter_character_col);
        temp_symbol = token_for_col;
    }
    fclose(fs);
}


int main() {

    delimiter_character_col = "\t";
    delimiter_character_line = "\n";
    fileread = "instructions.txt";
    filewrite = "pass2.txt";
    filesymbol = "symbol.txt";
    fileMOT = "MOT.txt";

    fr = fopen( fileread, "r" );
    fw = fopen( filewrite, "w" );

    char line[BUFFER];
    char *token_for_col;
    char *token_for_col_line;
    char *token_for_line_1;
    char *token_for_line_2;
    char *line_pointer_original;
    char *line_pointer;
    int flag = 0;

    while (fgets(line, BUFFER, fr)) {

        line_pointer = strdup(line);
        line_pointer_original = strdup(line);

        token_for_line_1 = (char *)strtok(line, delimiter_character_line);
        token_for_line_2 = (char *)strtok(line_pointer, delimiter_character_line);

        token_for_col_line = (char *)strtok(token_for_line_1, delimiter_character_col);
        token_for_col_line = (char *)strtok(NULL, delimiter_character_col);

        if (!strcmp(token_for_col_line, "START") || !strcmp(token_for_col_line, "USING")) {
            fprintf(fw, "%s", line_pointer_original);
        } else if ( find_in_MOT(token_for_col_line) ) {
            token_for_col = (char *)strtok(token_for_line_2, delimiter_character_col);
            token_for_col = (char *)strtok(NULL, delimiter_character_col);
            token_for_col = (char *)strtok(NULL, delimiter_character_col);

            char b[strlen(token_for_col) - 2];
            strncpy(b, token_for_col + 2, strlen(token_for_col) - 2);
            find_in_symbol_table(b);

            printf("%s\n", temp_symbol);
            printf("%s\t%s\n", temp_literal, temp_symbol);
            fprintf(fw, "%s\t%s\t%s\n", "#", temp_literal, temp_symbol);
        } else {
            fprintf(fw, "%s", line_pointer_original);
        }
    }

    fclose(fr);
    fclose(fw);
}
