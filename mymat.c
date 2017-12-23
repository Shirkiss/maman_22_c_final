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
    char command[30];
    int i;
    FOREVER if (scanf("%s", command) == 1) {
            flag = FUNCTION_PART;
            for (i = 0; cmd[i].func != NULL; i++)
                if (strcmp(command, cmd[i].name) == 0)
                    break;
            if (cmd[i].func == NULL) {
                if (command[(strlen(command) - 1)] == ',')
                    fprintf(stderr, "\nInvalid comma after command name\n");
                else
                    fprintf(stderr, "Unknown command name: %s\n", command);
                not_valid();
            } else
                (*(cmd[i].func))();
        }

    return 0;
}