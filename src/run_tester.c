#include "../includes/tester.h"

static void close_fds(int fd[2]) {
    close(fd[0]);
    close(fd[1]);
}

static void print_valgrind(int status) {
    switch (status)
    {
    case 10752:
        printf("Valgrind ❌\n\n");
        break;
    case 6:
        printf("❌ SEG FAULT ❌\n\n");
        break;
    default:
        printf("Valgrind ✅\n\n");
        break;
    }
}

static void print_is_correct(int is_correct) {
    if (is_correct) {
        printf("Correct ✅\n");
    } else {
        printf("Incorrect ❌\n");
    }
}

static int check_content(char *err, char *out) {
    int have_content = 1;
    int i = 0;

    if (!out[0])
        have_content = 0;
    while (err[i]) {
        if (i == 0 && err[i] != '=')
            return 1;
        if (i > 0 && err[i - 1] == '\n' && err[i] != '=')
            return 1;
        i++;
    }
    return (have_content);
}

static int check_opening(int have_content, char initial) {
    if ((have_content && initial == '0') || (!have_content && initial == '1'))
        return (1);
    else
        return (0);
}

static int execute_cub(char *path, int *status){
    int fd_err[2];
    int fd_out[2];
    char err_buffer[4096];
    char out_buffer[4096];

    pipe(fd_out);
    pipe(fd_err);
    char *args[] = { "valgrind",
                    "--leak-check=full",
                    "--error-exitcode=42",
                    "./cub3D",
                    path,
                    NULL };
    pid_t pid = fork();
    if (pid == 0) {
        dup2(fd_err[1], STDERR_FILENO);
        dup2(fd_out[1], STDOUT_FILENO);
        close_fds(fd_err);
        close_fds(fd_out);
        if (execvp("valgrind", args) == -1)
            exit(printf("error opening your cub3D, check if this is the rigth path: '../cub3D'\n"));
    }
    close(fd_out[1]);
    close(fd_err[1]);
    sleep(2);
    kill(pid, SIGINT);
    waitpid(pid, status, 0);
    read(fd_err[0], err_buffer, sizeof(err_buffer));
    read(fd_out[0], out_buffer, sizeof(out_buffer));
    return (check_content(err_buffer, out_buffer));
}

void run_tester(t_maps *maps) {
    int status;
    int index = 0;
    int corrects = 0;

    while (maps) {
        printf("testing: %s\n", &maps->path[18]);
        int have_content = execute_cub(maps->path, &status);
        int is_correct = check_opening(have_content, maps->path[18]);
        if (is_correct && status != 10752 && status != 6)
            corrects++;
        print_is_correct(is_correct);
        print_valgrind(status);
        maps = maps->next;
        index++;
    }
    printf("-------------------------------------------------\n");
    printf("All tests finished.\nFinal result is: %d of %d\n", corrects, index);
    if (index == corrects)
        printf("Congratulations 🎉🎉\n");
}
