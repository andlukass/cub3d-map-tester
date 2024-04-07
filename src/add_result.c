#include "../includes/tester.h"

void add_result(t_results **results, char *err, char *out) {
    t_results *new_node = malloc(sizeof(t_results));
    t_results *curr;
    if (new_node == NULL)
        return ;
    new_node->next = NULL;
    strcpy(new_node->std_err, err);
    strcpy(new_node->std_out, out);
    curr = *results;
    if (!*results)
        *results = new_node;
    else {
        while (curr->next){
            curr = curr->next;
        }
        curr->next = new_node;
    }
}