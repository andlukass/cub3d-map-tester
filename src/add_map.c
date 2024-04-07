#include "../includes/tester.h"

void add_map(t_maps **maps, char *path) {
    t_maps *new_node = malloc(sizeof(t_maps));
    t_maps *curr;
    if (new_node == NULL)
        return ;
    new_node->next = NULL;
    strcpy(new_node->path, "./map_tester/maps/");
    strcat(new_node->path, path);
    curr = *maps;
    if (!*maps)
        *maps = new_node;
    else {
        while (curr->next){
            curr = curr->next;
        }
        curr->next = new_node;
    }
}