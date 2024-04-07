#include "../includes/tester.h"

void print_map(t_maps *maps) {
    while (maps){
        printf("%s\n", maps->path);
        maps = maps->next;
    }
}

void close_fds(int fd[2]){
    close(fd[0]);
    close(fd[1]);
}

void run_tester(t_results **results, t_maps *maps){
    pid_t pid;
    int fd_err[2];
    int fd_out[2];
    char err_buffer[4096];
    char out_buffer[4096];

    pipe(fd_err);
    pipe(fd_out);
    while (maps) {
        char *args[] = {"cub3D", maps->path, NULL};
        printf("testing: %s\n", &maps->path[18]);
        pid = fork();

         if (pid == 0) {
            dup2(fd_err[1], STDERR_FILENO);
            dup2(fd_out[1], STDOUT_FILENO);
            close_fds(fd_err);
            close_fds(fd_out);
            if (execv("./cub3D", args) == -1)
                exit(printf("error opening your cub3D, check if this is the rigth path: '../cub3D'\n"));
        }
        close(fd_err[1]);
        close(fd_out[1]);
        sleep(2);
        kill(pid, SIGINT);
        read(fd_err[0], err_buffer, sizeof(err_buffer));
        read(fd_out[0], out_buffer, sizeof(out_buffer));
        add_result(results, err_buffer, out_buffer);
        maps = maps->next;
    }
}

int main() {
    t_maps *maps;
    t_results *results;

    maps = NULL;
    results = NULL;
    if (!get_maps(&maps))
        return (printf("error getting maps\n"));
    change_dir("../");
    // print_map(maps);
    run_tester(&results, maps);
   

    return 0;
}