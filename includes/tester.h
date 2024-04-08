#ifndef TESTER_H
# define TESTER_H

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_results {
    char std_out[4096];
    char std_err[4096];
    struct s_results *next;
} t_results;

typedef struct s_maps {
    char path[1024];
    struct s_maps *next;
} t_maps;

void add_result(t_results **results, char *err, char *out);
void add_map(t_maps **maps, char *path);
void run_tester(t_results **results, t_maps *maps);
void change_dir(char *new_directory);
int get_maps(t_maps **maps);

#endif