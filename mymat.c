/*
 * File name: mymat.c
 * Program: matrix calculator program that support the following commands:
 * 1. Read Matrix (read_mat)
 * 2. Print Matrix (print_mat)
 * 3. Addition of Matrices (add_mat)
 * 4. subtraction of Matrices (add_mat)
 * 5. Multiplication of Matrices (mul_mat)
 * 6. Transposition of Matrix (trans_mat)
 * 7. Multiplication of Matrix by scalar (mul_scalar)
 * 8. Stopping the program (stop)
 *
 * The validate the user input and printing errors if needed
 */

#include "mat.h"

struct {
    char *name;

    void (*func)(void);
} cmd[] = {
        {"read_mat",   read_mat},
        {"print_mat",  print_mat},
        {"add_mat",    add_mat},
        {"sub_mat",    sub_mat},
        {"mul_mat",    mul_mat},
        {"trans_mat",  trans_mat},
        {"mul_scalar", mul_scalar},
        {"stop",       stop},
        {"not_valid", NULL}
};


int main(void) {
    char line[MAXOP];
    char *command;
    char *newline;
    int i;
    FOREVER if (fgets(line, MAXOP, stdin) != NULL) {
            /*skip empty lines*/
            if (line[0] == '\n') {
                continue;
            }
            /*print entered command*/
            printf("\nCommand: %s\n", line);
            /*create a copy of the line*/
            line_ptr = calloc(strlen(line) + 1, sizeof(char));
            strcpy(line_ptr, line);
            /*extract the command from line*/
            command = strtok(line, " ");

            /*remove \n from the command in case of "stop" command*/
            newline = strchr( command, '\n' );
            if ( newline )
                *newline = 0;

            /*line_ptr have all the line except for the command*/
            line_ptr = line_ptr + strlen(command);
            flag = FUNCTION_PART;
            for (i = 0; cmd[i].func != NULL; i++)
                if (strcmp(command, cmd[i].name) == 0)
                    break;
            if (cmd[i].func == NULL) {
                /*error: comma after command line (without space between)*/
                if (command[(strlen(command) - 1)] == ',')
                    fprintf(stderr, "\nInvalid comma after command name\n");
                else
                    fprintf(stderr, "\nUnknown command name: %s\n", command);
                not_valid();
            } else
                /*call the function*/
                (*(cmd[i].func))();
        }

    return 0;
}

/*stop the program*/
void stop(void) {
    printf("********End of the program*******\n");
    exit(0);
}

