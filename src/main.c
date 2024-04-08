#include "../includes/tester.h"

void print_map(t_maps *maps) {
    while (maps){
        printf("%s\n", maps->path);
        maps = maps->next;
    }
}

int main() {
    t_maps *maps;

    maps = NULL;
    if (!get_maps(&maps))
        return (printf("error getting maps\n"));
    change_dir("../");
    run_tester(maps);
    return 0;
}