#include "../includes/tester.h"
#include <dirent.h>

int get_maps(t_maps **maps) {
    int size;
    DIR *directory;
    struct dirent *entry;

    size = 0;
    change_dir("./maps");
    directory = opendir(".");
    while ((entry = readdir(directory)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        add_map(maps, entry->d_name);
        size++;
    }
    change_dir("../");
    return (size);
}