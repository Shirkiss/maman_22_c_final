#include "mat.h"


typedef struct tnode {
    matrix *first_parm;
    matrix *second_parm;
    matrix *result;
} params;

params temp_parm;

void read_mat(void) {
    double *q;
    double number = 0;
    char s[MAXOP];
    flag = PARAMS_PART;
    temp_parm.first_parm = get_parameters();

    if (temp_parm.first_parm == NULL) {
        fprintf(stderr, "\nUndefined matrix name\n");
        not_valid();
    } else {
        flag = OPERANDS_PART;
        for (q = (double *) (temp_parm.first_parm); (q < (double *) (temp_parm.first_parm) + (SIZE * SIZE)); q++) {
            number = getop(s);
            if (flag == END_OF_LINE_PART) {
                *q = number;
                q++;
                while (q < (double *) (temp_parm.first_parm) + (SIZE * SIZE)) {
                    *q = 0;
                    q++;
                }
                break;
            } else if (flag == ERROR) {
                not_valid();
                break;
            } else {
                *q = number;
            }
        }
        if (flag == OPERANDS_PART) {
            flag = EXTRA_PART;
            while (flag == EXTRA_PART)
                getop(s);
        }
    }
}


void print_mat(void) {
    int row, columns;
    flag = END_OF_LINE_PART;
    temp_parm.first_parm = get_parameters();

    if (temp_parm.first_parm == NULL)
        not_valid();


    for (row = 0; row < SIZE && flag != ERROR; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            printf("%.02f	", (*temp_parm.first_parm)[row][columns]);
        }
        printf("\n");
    }
}

void add_mat(void) {
    int row, columns;
    flag = PARAMS_PART;
    temp_parm.first_parm = get_parameters();
    temp_parm.second_parm = get_parameters();
    flag = END_OF_LINE_PART;
    temp_parm.result = get_parameters();

    if (temp_parm.first_parm == NULL || temp_parm.second_parm == NULL || temp_parm.result == NULL)
        not_valid();

    for (row = 0; row < SIZE && flag != ERROR; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            (*temp_parm.result)[row][columns] = (*temp_parm.first_parm)[row][columns] +
                                                (*temp_parm.second_parm)[row][columns];
        }
    }
}

void sub_mat(void) {
    int row, columns;
    flag = PARAMS_PART;
    temp_parm.first_parm = get_parameters();
    temp_parm.second_parm = get_parameters();
    flag = END_OF_LINE_PART;
    temp_parm.result = get_parameters();

    if (temp_parm.first_parm == NULL || temp_parm.second_parm == NULL || temp_parm.result == NULL)
        not_valid();

    for (row = 0; row < SIZE && flag != ERROR; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            (*temp_parm.result)[row][columns] =
                    (*temp_parm.first_parm)[row][columns] - (*temp_parm.second_parm)[row][columns];
        }
    }
}

void mul_mat(void) {
    int row, columns, inner;
    flag = PARAMS_PART;
    temp_parm.first_parm = get_parameters();
    temp_parm.second_parm = get_parameters();
    if (flag != ERROR)
        flag = END_OF_LINE_PART;
    temp_parm.result = get_parameters();
    if (temp_parm.first_parm == NULL || temp_parm.second_parm == NULL || temp_parm.result == NULL)
        not_valid();

    for (row = 0; row < SIZE && flag != ERROR; row++) {
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
    flag = PARAMS_PART;
    temp_parm.first_parm = get_parameters();
    flag = END_OF_LINE_PART;
    temp_parm.result = get_parameters();

    if (temp_parm.first_parm == NULL || temp_parm.result == NULL)
        not_valid();

    for (row = 0; row < SIZE && flag != ERROR; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            (*temp_parm.result)[columns][row] += (*temp_parm.first_parm)[row][columns];
        }
    }
}


void stop(void) {
    printf("********End of the program*******\n");
    exit(0);
}

void mul_scalar(void) {
    int row, columns;
    double scalar;
    char s[MAXOP];

    flag = PARAMS_PART;
    temp_parm.first_parm = get_parameters();
    scalar = getop(s);
    flag = END_OF_LINE_PART;
    temp_parm.result = get_parameters();

    if (temp_parm.first_parm == NULL || temp_parm.result == NULL)
        not_valid();


    for (row = 0; row < SIZE && flag != ERROR; row++) {
        for (columns = 0; columns < SIZE; columns++) {
            (*temp_parm.result)[columns][row] = (*temp_parm.first_parm)[row][columns] * scalar;
        }
    }

}

void not_valid(void) {
    flag = ERROR;
    while ((getchar()) != '\n');
}





