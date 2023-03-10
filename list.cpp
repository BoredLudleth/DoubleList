#include "list.hpp"

void list_ctor (struct List* myList) {
    myList->list = (struct elem*) calloc (LIST_LENGTH + 1,  sizeof (struct elem));

    myList->head = 1;
    myList->tail = 1;
    myList->free = -1;
    myList->length = 0;

    myList->list[0].next = myList->tail;
    myList->list[0].prev = myList->head;

    for (int i = 1; i < LIST_LENGTH - 1; i++) {
        myList->list[i].next = - i - 1;
        myList->list[i].prev = 0;
    }

    for (int i = 0; i < LIST_LENGTH; i++) {
        myList->list[i].data = POISON;
    }
    
    myList->list[LIST_LENGTH - 1].next = 0;

    list_check (myList);
}

void list_dtor (struct List* myList) {
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
//отоброжать пустые и служебный

void list_insert_before (struct List* myList, type value, int index) {
    if (LIST_LENGTH < index || index < 0 || myList->length > LIST_LENGTH || myList->free == 0) {
        printf ("We can't add your value\n");
        myList->errors = INSERT_ERROR;

        return;
    }
    
    list_check (myList);

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
        myList->list[0].prev = myList->head;
    }

    myList->length++;

    list_check (myList);
}

void list_first (struct List* myList, type value) {
    list_insert_before (myList, value, list_log_in_phys(myList, myList->head));
}//TEST_ME

void list_last (struct List* myList, type value) {
    list_insert_after (myList, value, list_log_in_phys(myList, myList->tail));
}//TEST_ME

void list_insert_after (struct List* myList, type value, int index) {
    if (LIST_LENGTH < index || index < 0 || myList->length > LIST_LENGTH || myList->free == 0) {
        printf ("We can't add your value\n");
        myList->errors = INSERT_ERROR;
        return;
    }

    list_check (myList);

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
        myList->list[0].next = myList->tail;
    }

    myList->list[insertBlock].data = value;

    myList->length++;

    list_check (myList);
}

int list_search (struct List* myList, type value) {
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

int list_log_in_phys (struct List* myList, type index) {
    int current = myList->head;
    for (int i = 1; i < index; i++, current = myList->list[current].next) {}

    for (int i = 0; i < LIST_LENGTH + 1; i++) {
        if (myList->list[current].data == myList->list[i].data && myList->list[current].prev == myList->list[i].prev) {
            return i;
        }        
    }

    printf ("No element with such adress\n");
    return -1;
}

int list_phys_in_log (struct List* myList, int index) {
    for (int current = myList->head, j = 0; current != 0; current = myList->list[current].next) {
        j++;
        if (myList->list[index].data == myList->list[current].data && myList->list[index].prev == myList->list[current].prev) {
            return j;
        }
    }

    printf ("No element with such adress\n");
    return -1;
}

int list_delete_first (struct List* myList) {
    int result = list_delete (myList, list_log_in_phys(myList, 1));
    return result;
}//TEST_ME

int list_delete_last (struct List* myList) {
    int result = list_delete (myList, list_log_in_phys(myList, myList->length));
    return result;
}//TEST_ME

int  list_delete (struct List* myList, type index) {
    if (myList->list[index].data == POISON) {
        printf("You can't delete unexisting thing(\n");
        myList->errors = DELETE_ERROR;
        return 0;
    }

    list_check (myList);

    int delValue = myList->list[index].data;

    myList->list[index].data = POISON;

    if (index != myList->tail) {
        myList->list[myList->list[index].next].prev = myList->list[index].prev;
    } else {
        myList->tail = myList->list[index].prev;
        myList->list[0].next = myList->tail;
    }

    if (index != myList->head) {
        myList->list[myList->list[index].prev].next = myList->list[index].next;
    } else {
        myList->head = myList->list[index].next;
        myList->list[0].prev = myList->head;
    }

    myList->list[index].next = myList->free;
    myList->list[index].prev = 0;
    myList->free = -index;
    (myList->length)--;

    printf ("DELETED VALUE: %d\n", delValue);

    list_check (myList);

    return 1;

}

void list_dump (const struct List*  myList) {
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
        case CONNECT_ERROR:
            printf ("LIST CONNECTION PROBLEM\n");
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

    printf ("SPEC%d ", 0);
    printf (TYPE_SPECIFICATOR_FIVE, myList->list[0].data);
    printf (" head%4d tail%4d\n", myList->list[0].prev, myList->list[0].next);
    for (int i = 1; i < LIST_LENGTH + 1; i++) {
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

int list_check (struct List* myList) {
    if (myList->length <= 1) {
        return 0;
    }
    int lr_counter = 0;

    for (int current = myList->head; current != 0; current = myList->list[current].next) {
        if (current != 0) {
            lr_counter++;
        }
    }

    for (int current = myList->head; current != 0; current = myList->list[current].next) {
        if (current != myList->tail && myList->list[current].data != myList->list[myList->list[myList->list[current].next].prev].data) {
            myList->errors = CONNECT_ERROR;
            break;
        }

        if (current != myList->head && myList->list[myList->list[myList->list[current].prev].next].data != myList->list[current].data) {
            myList->errors = CONNECT_ERROR;
            break;
        }
    }

    int rl_counter = 0;
    
    for (int current = myList->tail; current != 0; current = myList->list[current].prev) {
        if (current != 0) {
            rl_counter++;
        }
    }

    if (lr_counter != myList->length || rl_counter != myList->length) {
        myList->errors = CONNECT_ERROR;
    }

    if (myList->errors != 0) {
        list_dump (myList);
        return 1;
    } else {
        return 0;
    }
}

char* inttoa(int n, char* s) {
    int i = 0;
    int sign = 0;
 
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = (char) (n % 10) + '0';
    } while ((n /= 10) > 0);    
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);

    return s;
}

void reverse(char* s) {
    int i = 0, j = 0;
    char c = ' ';

    for (i = 0, j = (int) strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void graph_dump (struct List* myList) {
    static int num = 0;
    char name_of_file[15] = "image";
    char im_num[5] = {};
    strcat (name_of_file, inttoa(num, im_num));
    strcat (name_of_file, ".txt\0");

    char pic_name[15] = "image";
    strcat (pic_name, im_num);
    strcat (pic_name, ".png\0");

    num++;

    FILE* output = fopen (name_of_file,"w+");
    myList->output = output;
    if  (myList->output == nullptr) {
        printf ("File didn't open\n");
    }

    fprintf (myList->output, "digraph D \n{\n");
    fprintf (myList->output, "node [shape=record fontname=Arial];\n");
    fprintf (myList->output, "rankdir = HR;\n");

    for (int i = 0; i < LIST_LENGTH; i++) {
        if (myList->list[i].next < 0 || myList->list[i].data == POISON) {
            continue;
        }
        fprintf (myList->output, "node%d [label = \"<f0>value = %d |{prev = %d|<f1> addr = %d|<f2> next %d}\", style = filled, fillcolor = \"#d0ffff\"];\n",  i, myList->list[i].data, 
                 list_log_in_phys(myList, myList->list[i].prev), 
                 list_log_in_phys(myList, i),
                 list_log_in_phys(myList, myList->list[i].next));
    }

    for (int i = 0; i < LIST_LENGTH; i++) {
        if (myList->list[i].data == POISON || myList->list[i].next ==  0) {
            continue;
        }
        fprintf (myList->output, "node%d -> node%d [dir=both, color = \"#00D000\"];\n", i, myList->list[i].next);
    }

    fprintf (myList->output, "}\n");
    fclose (myList->output);
    myList->output = nullptr;

    char command[40] = "dot ";
    strcat (command, name_of_file);
    strcat (command, " -Tpng -o ");
    strcat (command, pic_name);

    system(command);
}

void list_linearization (struct List* myList) {
    if (myList->length == 0) {
        return;
    }

    type* myLittleArrayOfValues = (type*) calloc (myList->length,  sizeof (type));

    for (int current = myList->head, i = 0; current != 0; current = myList->list[current].next, i++)  {
        myLittleArrayOfValues[i] = myList->list[current].data;
    }

    for (int i = 1, j = 0; j < LIST_LENGTH; i++, j++) {
        if (j< myList->length) {
            myList->list[i].prev = i - 1;
            myList->list[i].data = myLittleArrayOfValues[j];
            if (i == myList->length) {
                myList->list[i].next = 0;
            } else {
                myList->list[i].next = i + 1;
            }
        } else {
            myList->list[i].prev = 0;
            myList->list[i].data = POISON;
            if (i == LIST_LENGTH) {
                myList->list[i].next = 0;
            } else {
                myList->list[i].next = - i - 1;
            }
        }
    }

    myList->head = 1;
    myList->tail = myList->length;
    myList->free = - myList->length - 1;

    myList->list[0].next = myList->tail;
    myList->list[0].prev = myList->head;

    free (myLittleArrayOfValues);
    myList->flag_linear = 1;
}

int scanf_check (int x) {
    if (x == 0) {
        printf ("Undefined command\n");
        while (getchar() != '\n');

        return 0;
    }

    return 1;
}
