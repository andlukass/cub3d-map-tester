#include "../includes/tester.h"

void print_map(t_maps *maps) {
    while (maps){
        printf("%s\n", maps->path);
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