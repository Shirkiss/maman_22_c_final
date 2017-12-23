#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 4
#define FOREVER for(;;)
#define MAXOP 100
#define BUFSIZE 100
#define FUNCTION_PART 0
#define PARAMS_PART 1
#define OPERANDS_PART 2
#define END_OF_LINE_PART 3
#define ERROR 4
#define EXTRA_PART 5

int flag;

typedef double matrix[SIZE][SIZE];

void read_mat(void);
void add_mat(void);
double getop(char s[]);
void print_mat(void);
matrix *get_parameters(void);
void mul_scalar(void);
void stop(void);
void trans_mat(void);
void mul_mat(void);
void sub_mat(void);
void not_valid(void);






