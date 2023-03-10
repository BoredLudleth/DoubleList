#include "list.hpp"

void list_ctor (struct spis* myList) {
    myList->list = (struct elem*) calloc (LIST_LENGTH + 1,  sizeof (struct elem));

    myList->head = 1;
    myList->tail = 1;
    myList->free = -1;
    myList->length = 0;

    myList->list[0].next = myList->head;
    myList->list[0].prev = myList->tail;

    for (int i = 1; i < LIST_LENGTH - 1; i++) {
        myList->list[i].next = - i - 1;
        myList->list[i].prev = 0;
    }

    for (int i = 0; i < LIST_LENGTH; i++) {
        myList->list[i].data = POISON;
    }
    
    myList->list[LIST_LENGTH - 1].next = 0;

    list_сheck (myList);
}

void list_dtor (struct spis* myList) {
    myList->head = 0;
    myList->tail = 0;
    myList->free = 0;

    for (int i = 0; i < LIST_LENGTH; i++) {
        myList->list[i].prev = POISON;
        myList->list[i].data = POISON;
        myList->list[i].next = POISON;
    }

    free (myList->list);
    myList->list = nullptr;
}

void list_insert_before (struct spis* myList, type value, int index) {
    if (LIST_LENGTH < index || index < 0 || myList->length > LIST_LENGTH || myList->free == 0) {
        printf ("We can't add your value\n");
        myList->errors = INSERT_ERROR;

        return;
    }
    
    list_сheck (myList);

    if (myList->length == 0) {
        int insertBlock = -myList->free;

        myList->free = myList->list[-myList->free].next;
        myList->list[insertBlock].data = value;
        myList->list[insertBlock].prev = 0;
        myList->list[insertBlock].next = 0;

        myList->head = insertBlock;
        myList->tail = insertBlock;
        myList->length++;

        return;
    }

    int insertBlock = -myList->free;

    myList->free = myList->list[-myList->free].next;

    myList->list[insertBlock].prev = myList->list[index].prev;
    myList->list[insertBlock].next = index;
    myList->list[index].prev = insertBlock;

    myList->list[insertBlock].data = value;

    if (myList->list[insertBlock].prev != 0) {
        myList->list[myList->list[insertBlock].prev].next = insertBlock;
    } else {
        myList->head = insertBlock;
    }

    myList->length++;

    list_сheck (myList);
}

void list_insert_after (struct spis* myList, type value, int index) {

}



void list_insert_after (struct spis* myList, type value, int index) {
    if (LIST_LENGTH < index || index < 0 || myList->length > LIST_LENGTH || myList->free == 0) {
        printf ("We can't add your value\n");
        myList->errors = INSERT_ERROR;
        return;
    }

    list_сheck (myList);

    if (myList->length == 0) {
        int insertBlock = -myList->free;

        myList->free = myList->list[-myList->free].next;
        myList->list[insertBlock].data = value;
        myList->list[insertBlock].prev = 0;
        myList->list[insertBlock].next = 0;

        myList->head = insertBlock;
        myList->tail = insertBlock;
        myList->length++;

        return;
    }

    int insertBlock = -myList->free;

    myList->free = myList->list[-myList->free].next;

    myList->list[insertBlock].next = myList->list[index].next;
    myList->list[insertBlock].prev = index;
    myList->list[index].next = insertBlock;
    
    if (myList->list[insertBlock].next != 0) {
        myList->list[myList->list[insertBlock].next].prev = insertBlock;
    } else {
        myList->tail = insertBlock;
    }

    myList->list[myList->list[insertBlock].next].prev = index;

    myList->list[insertBlock].data = value;

    myList->length++;

    list_сheck (myList);
}
//insert before next or tail - don't fixes, need physical in logical (or adress)

int list_search (struct spis* myList, type value) {
    int current = myList->head;
    if (myList->length != 0) {
        while (current > 0) {
            if (myList->list[current].data == value) {
                return current;
            }
            current = myList->list[current].next;
        }
    }

    return -1;
}

struct elem* list_log_in_phys (struct spis* myList, type index) {
    if (index == 0) {
        return 0;
    }
    return &(myList->list[index]);
}

int list_phys_in_log (struct spis* myList, struct elem* Element) {
    int current = myList->head;

    if (myList->length == 0) {
        printf ("No such element in list\n");

        return -1;
    }

    while (current != 0) {
        if (&(myList->list[current]) == Element) {
            return current;

            break;
        } else {
            current = myList->list[current].next;
        }
    }

    printf ("No such element in list\n");

    return -1;
}

int  list_delete (struct spis* myList, type index) {
    if (myList->list[index].data == POISON) {
        printf("You can't delete unexisting thing(\n");
        myList->errors = DELETE_ERROR;
        return 0;
    }

    list_сheck (myList);

    int delValue = myList->list[index].data;

    myList->list[index].data = POISON;

    if (index != myList->tail) {
        myList->list[myList->list[index].next].prev = myList->list[index].prev;
    } else {
        myList->tail = myList->list[index].prev;
    }

    if (index != myList->head) {
        myList->list[myList->list[index].prev].next = myList->list[index].next;
    } else {
        myList->head = myList->list[index].next;
    }

    myList->list[index].next = myList->free;
    myList->list[index].prev = 0;
    myList->free = -index;
    (myList->length)--;

    printf ("DELETED VALUE: %d\n", delValue);

    list_сheck (myList);

    return 1;

}

void list_dump (const struct spis*  myList) {
    printf ("==========LIST_DUMP==========\n");

    printf ("ERRORS: %d\n", myList->errors);

    switch (myList->errors) {
        case NO_ERRORS:
            printf ("NO PROBLEMS\n");
            break;
        case INSERT_ERROR:
            printf ("INSERT ERROR\n");
            break;
        case DELETE_ERROR:
            printf ("DELETE PROBLEM\n");
            break;
        default:
            printf ("LIST DEFENDER WAS HAHAcked\n");
            break;
    };

    printf ("length: %d\n", myList->length);
    printf ("head: %d\n", myList->head);
    printf ("tail: %d\n", myList->tail);
    printf ("free: %d\n", myList->free);

    printf ("    № data  prev next\n");

    for (int i = 0; i < LIST_LENGTH; i++) {
        printf ("%5d ", i);
        printf (TYPE_SPECIFICATOR_FIVE, myList->list[i].data);
        printf ("%4d %4d\n", myList->list[i].prev, myList->list[i].next);
    }

    printf ("HUMAN VIEW\n");

    int current = myList->head;

    while (current != 0 && myList->length != 0) {
        printf (TYPE_SPECIFICATOR, myList->list[current].data);
        printf (" <-> ");
        current = myList->list[current].next;
    }

    printf ("end\n=============================\n");
}

int list_сheck (struct spis* myList) {
    if (myList->errors != 0) {
        list_dump (myList);
        return 1;
    } else {
        return 0;
    }
}

void mdDo (FILE* output, struct spis* myList) {
    fprintf (output, "digraph D \n{\n");

    for (int i = 0; i < LIST_LENGTH; i++) {
        if (myList->list[i].next < 0 || myList->list[i].data == POISON) {
            continue;
        }
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

    fprintf (output, "}\n");
}

//linearization - sort - don't do  it now
int scanf_check (int x) {
    if (x == 0) {
        printf ("Undefined command\n");
        while (getchar() != '\n');

        return 0;
    }

    return 1;
}
