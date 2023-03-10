#include "graphviz.hpp"

void mdBegin (FILE* output) {
    fprintf (output, "digraph D \n{\n");
}

void mdDo (FILE* output, struct spis* myList) {
    mdBegin (output);

    for (int i = 0; i < LIST_LENGTH; i++) {
        if (myList->list[i].next < 0 || myList->list[i].data == POISON) {
            continue;
        }
        //if ()
        fprintf (output, "node%d [label = \"value = %d \\n prev = %p \\n addr = %p \\n next %p\"];\n",  i, myList->list[i].data, 
                 list_log_in_phys(myList, myList->list[i].prev), 
                 list_log_in_phys(myList, i),
                 list_log_in_phys(myList, myList->list[i].next));
    }

    for (int i = 0; i < LIST_LENGTH; i++) {
        if (myList->list[i].data == POISON || myList->list[i].next ==  0) {
            continue;
        }
        fprintf (output, "node%d -> node%d;\n", i, myList->list[i].next);
    }

    mdEnd (output);
}

void mdEnd (FILE* output) {
    fprintf (output, "}\n");
}