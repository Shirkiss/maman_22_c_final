#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 4
#define FOREVER for(;;)
#define OK 1
#define MAXOP 100

typedef double matrix[SIZE][SIZE];
char s[MAXOP];

double getop();

double *get_mat_address(void);

void add_mat(void);

int get_mat_index(void);

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
        {'f', &MAT_F},
        {'A', &MAT_A},
        {'B', &MAT_B},
        {'C', &MAT_C},
        {'D', &MAT_D},
        {'E', &MAT_E},
        {'F', &MAT_F},
        {'#', NULL},
};

typedef struct tnode {
    matrix *first_parm;
    matrix *second_parm;
    matrix *result;
} params;

params temp_parm;
int flag = 0;

void read_mat(void) {
    double *q;
    int i;
    double number;
    i = get_mat_index();

    if (mats[i].mat == NULL)
        fprintf(stderr, "Matrix does not exist\n");

    flag = 0;
    for (q = (double *) (mats[i].mat); q < (double *) (mats[i].mat) + (SIZE * SIZE); q++) {
        number = getop(s);
        if (flag == 1) {
            *q = number;
            while (q++ < (double *) (mats[i].mat) + (SIZE * SIZE)) {
                *q = 0;
                q++;
                printf("%f\n", *q);
            }
            break;
        } else {
            *q = number;
            printf("%f\n", *q);
        }
    }

}


double getop() {
    int i, c;

    while ((s[0] = c = my_getch()) == ' ' || c == ',');
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') {
        fprintf(stderr, "invalid char\n");
        exit(0);
    }
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = my_getch()));
    if (c == '-') {
        while (isdigit(s[++i] = c = my_getch()));
        if (i == 1 && c != '.') /*minus sign alone*/
        {
            fprintf(stderr, "invalid char\n");
            exit(0);
        }
    }
    if (c == '.')
        while (isdigit(s[++i] = c = my_getch()));
    if (c == '\n' || c == EOF) {
        flag = 1;
        printf("we are in the end \n");
    }
    s[i] = '\0';
    printf("atof %f\n", atof(s));
    return atof(s);
}

#define BUFSIZE 100

char buf[BUFSIZE]; /*to define the number in the header*/
int bufp = 0;

int my_getch(void) {

    return (bufp > 0 ? buf[--bufp] : getchar());
}

int my_ungetch(int c) {

    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters");
    else
        buf[bufp++] = c;
}


void print_mat(void) {
    int row, columns;
    int mat_index;

    mat_index = get_mat_index();

    for (row = 0; row < SIZE; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            printf("%.02f	", ((double *) mats[mat_index].mat)[row * SIZE + columns]);
        }
        printf("\n");
    }

}

void add_mat(void) {
    int row, columns;
    int first_index, second_index, result_index;


    first_index = get_mat_index();
    second_index = get_mat_index();
    result_index = get_mat_index();

    temp_parm.first_parm = mats[first_index].mat;
    temp_parm.second_parm = mats[second_index].mat;
    temp_parm.result = mats[result_index].mat;

    for (row = 0; row < SIZE; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            (*temp_parm.result)[row][columns] = (*temp_parm.first_parm)[row][columns] +
                                                (*temp_parm.second_parm)[row][columns];
            printf("%.02f	", (*temp_parm.result)[row][columns]); /*debug*/
        }
        printf("\n");
    }
}

double *get_mat_address(void) {
    int i;

    i = get_mat_index();


    if (mats[i].mat == NULL)
        fprintf(stderr, "Matrix does not exist\n");
    else
        return (double *) (mats[i].mat);
}

int get_mat_index(void) {
    char mat_name[30];
    int i;
    char *p = mat_name;
    scanf("%s", mat_name);
    p = p + 4;
    p[1] = 0;
    printf("%s\n", p); /*debug*/

    for (i = 0; mats[i].mat != NULL; i++)
        if (*p == mats[i].name) {
            break;
        }
    return i;
}

void sub_mat(void) {
    int row, columns;
    int first_index, second_index, result_index;


    first_index = get_mat_index();
    second_index = get_mat_index();
    result_index = get_mat_index();

    temp_parm.first_parm = mats[first_index].mat;
    temp_parm.second_parm = mats[second_index].mat;
    temp_parm.result = mats[result_index].mat;

    for (row = 0; row < SIZE; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            ((double *) temp_parm.result)[row * SIZE + columns] =
                    ((double *) temp_parm.first_parm)[row * SIZE + columns] -
                    ((double *) temp_parm.second_parm)[row * SIZE + columns];
            printf("%.02f	", ((double *) temp_parm.result)[row * SIZE + columns]); /*debug*/
        }
        printf("\n");
    }
}

void mul_mat(void) {
    int row, columns, inner;
    int first_index, second_index, result_index;

    first_index = get_mat_index();
    second_index = get_mat_index();
    result_index = get_mat_index();

    temp_parm.first_parm = mats[first_index].mat;
    temp_parm.second_parm = mats[second_index].mat;
    temp_parm.result = mats[result_index].mat;


    for (row = 0; row < SIZE; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            for (inner = 0; inner < SIZE; inner++) {
                (*temp_parm.result)[row][columns] +=
                        (*temp_parm.first_parm)[row][inner] * (*temp_parm.second_parm)[inner][columns];
            }
        }


    }
}

void trans_mat(void) {

    int row, columns;
    int first_index, result_index;

    first_index = get_mat_index();
    result_index = get_mat_index();

    temp_parm.first_parm = mats[first_index].mat;
    temp_parm.result = mats[result_index].mat;


    for (row = 0; row < SIZE; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            (*temp_parm.result)[columns][row] += (*temp_parm.first_parm )[row][columns];
        }
    }

}


void stop(void) {
    printf("********End of the program*******\n");
    exit(0);
}

void mul_scalar(void){
    int row, columns;
    int first_index, result_index;
    double scalar;

    first_index = get_mat_index();
    scalar  = getop();
    result_index = get_mat_index();

    temp_parm.first_parm = mats[first_index].mat;
    temp_parm.result = mats[result_index].mat;


    for (row = 0; row < SIZE; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            (*temp_parm.result)[columns][row] = (*temp_parm.first_parm)[row][columns] * scalar;
        }
    }

}

void not_valid(void);

void prn_mat(matrix *mat);

matrix *get_parameters(void);

void get_data(matrix *mat);


struct {
    char *name;

    void (*func)(void);
} cmd[] = {
        {"read_mat",  read_mat},
        {"print_mat", print_mat},
        {"add_mat",   add_mat},
        {"sub_mat",   sub_mat},
        {"mul_mat",   mul_mat},
        {"trans_mat", trans_mat},
        {"mul_scalar", mul_scalar},
        {"stop",      stop},
        {"not_valid", NULL}
};


int main(void) {
    char command[30];
    int i;
    FOREVER if (scanf("%s", command) == 1) {
            for (i = 0; cmd[i].func != NULL; i++)
                if (strcmp(command, cmd[i].name) == 0)
                    break;
            if (cmd[i].func == NULL) {
                fprintf(stderr, "Command does not exist: %s\n", command);
                printf("not found"); /* FOR DEBUG */
            } else
                (*(cmd[i].func))();

        }

    return 0;
}
