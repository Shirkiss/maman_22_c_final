/*
 * File name: mymat.c
 * Program: Part of matrix calculator program
 * Contains text handling functions
 *
 */

#include "mat.h"


matrix MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;

struct {
    char name;
    matrix *mat;
} mats[] = {
        {'a', &MAT_A},
        {'b', &MAT_B},
        {'c', &MAT_C},
        {'d', &MAT_D},
        {'e', &MAT_E},
        {'e', &MAT_E},
        {'f', &MAT_F},
        {'A', &MAT_A},
        {'B', &MAT_B},
        {'C', &MAT_C},
        {'D', &MAT_D},
        {'E', &MAT_E},
        {'F', &MAT_F},
        {'#', NULL},
};

/*get operands*/
double getop(char s[]) {
    int i;
    char c;

    /*go over the line chars and ignoring while spaces or semicolons*/
    while ((s[0] = c = *(++line_ptr)) == ' ' || c == ',' || c == '\t');
    s[1] = '\0';
    /*if operand is not a number*/
    if (!isdigit(c) && c != '.' && c != '-' && flag != EXTRA_PART) {
        fprintf(stderr, "\nParameter not a real number\n");
        flag = ERROR;
        return 0;
    }
    i = 0;
    /*handle negative numbers*/
    if (c == '-') {
        while (isdigit(s[++i] = c = *(++line_ptr)));
        if (i == 1 && c != '.') /*minus sign alone*/
        {
            fprintf(stderr, "\nParameter not a real number\n");
            flag = ERROR;
            return 0;
        }
    }
    /*handle more than 1 digit numbers*/
    else if (isdigit(c))
        while (isdigit(s[++i] = c = *(++line_ptr)));
    /*handle fractures*/
    if (c == '.')
        while (isdigit(s[++i] = c = *(++line_ptr)));
    /*mark end of line*/
    if (c == '\n' || c == EOF) {
        flag = END_OF_LINE_PART;
    }
    s[i] = '\0';
    return atof(s);
}

/*get functions parameteres*/
matrix *get_parameters(void) {
    char mat_name[30];
    int i;
    char c;
    char *p = mat_name;
    i = 0;
    if (flag == ERROR)
        return NULL;
    while ((mat_name[0] = c = *(++line_ptr)) == ' ' || c == '\t');
    /*multiple semicolons*/
    if (c == ',') {
        fprintf(stderr, "\nMultiple consecutive commas \n");
        return NULL;
    }
    /*missing parameter*/
    if (c == '\n') {
        fprintf(stderr, "\nMissing parameter \n");
        return NULL;
    }
    /*collect the matrix name*/
    while ((mat_name[++i] = c = *(++line_ptr)) != ' ' && c != '\n' && c != ',');
    if (c == ' ') {
        while ((c = *(++line_ptr)) == ' ');
    }
    /*handle when there is missing param without ',' before*/
    if (c == '\n' && flag != END_OF_LINE_PART) {
        fprintf(stderr, "\nMissing parameter  \n");
        return NULL;
    }
    if (c != ',' && flag != END_OF_LINE_PART) {
        fprintf(stderr, "\nMissing comma \n");
        return NULL;
    }
    /*if nothing wrong - find the Matrix name*/
    if ((c == '\n' && flag == END_OF_LINE_PART) || (flag == PARAMS_PART))  {
        /*return the end of line to the console*/
        mat_name[i] = '\0';
        p = p + 4;
        p[1] = 0;
        for (i = 0; mats[i].mat != NULL; i++)
            if (*p == mats[i].name) {
                break;
            }
        return mats[i].mat;
    } else {
        fprintf(stderr, "\nExtraneous text at end of command \n");
        return NULL;
    }
}

/*if the line is not valid skip to the next line*/
void not_valid(void) {
    flag = ERROR;
    while ((getchar()) != '\n');
}
