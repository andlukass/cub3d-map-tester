#ifndef TESTER_H
# define TESTER_H

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_maps {
    char path[1024];
    struct s_maps *next;
} t_maps;

void add_map(t_maps **maps, char *path);
void run_tester(t_maps *maps);
void change_dir(char *new_directory);
int get_maps(t_maps **maps);

#endif