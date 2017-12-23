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


double getop(char s[]) {
    int i, c;

    while ((s[0] = c = my_getch()) == ' ' || c == ',' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-' && flag != EXTRA_PART) {
        fprintf(stderr, "\nParameter not a real number\n");
        flag = ERROR;
        return 0;
    }
    i = 0;
    if (c == '-') {
        while (isdigit(s[++i] = c = my_getch()));
        if (i == 1 && c != '.') /*minus sign alone*/
        {
            fprintf(stderr, "\nParameter not a real number\n");
            flag = ERROR;
            return 0;
        }
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = my_getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = my_getch()));
    if (c == '\n' || c == EOF) {
        flag = END_OF_LINE_PART;
    }
    s[i] = '\0';
    return atof(s);
}

char buf[BUFSIZE]; /*to define the number in the header*/
int bufp = 0;

int my_getch(void) {

    return (bufp > 0 ? buf[--bufp] : getchar());
}

matrix *get_parameters(void) {
    char mat_name[30];
    int i, c;
    char *p = mat_name;
    i = 0;
    if (flag == ERROR)
        return NULL;
    while ((mat_name[0] = c = getchar()) == ' ' || c == '\t');
    if (c == ',') {
        fprintf(stderr, "\nMultiple consecutive commas \n");
        return NULL;
    }
    if (c == '\n') {
        fprintf(stderr, "\nMissing parameter \n");
        return NULL;
    }
    /*collect the matrix name*/
    while ((mat_name[++i] = c = getchar()) != ' ' && c != '\n' && c != ',');
    if (c == ' ') {
        while ((c = getchar()) == ' ');
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
    if ((c == '\n' && flag == END_OF_LINE_PART) || (flag == PARAMS_PART))  {
        mat_name[i] = '\0';
        p = p + 4;
        p[1] = 0;

        for (
                i = 0;
                mats[i].mat != NULL; i++)
            if (*p == mats[i].name) {
                break;
            }
        return mats[i].mat;

    } else {
        fprintf(stderr, "\nExtraneous text at end of command \n");
        return NULL;
    }
}
