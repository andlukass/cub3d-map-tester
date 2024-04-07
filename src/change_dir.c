#include "../includes/tester.h"

void change_dir(char *new_directory) {
    if (chdir(new_directory) != 0){
        printf("error changing path\n");
        exit(1);
    }
}