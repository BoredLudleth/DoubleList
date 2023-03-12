#include "list.hpp"

int main () {
    struct List myList = {};

    int command = -1;
    type push_value = 0;
    type search_value = 0;
    int index = 0;

    list_ctor (&myList); 
                printf ("henlo, it's menu for list\n");
                printf ("1 num index - push before\n");
                printf ("2 num index - push after\n");
                printf ("3 - list search\n");
                printf ("4 - list delete\n");
                printf ("5 - list dump\n");
                printf ("6 - menu\n");
                printf ("7 index - logical adress to physical\n");
                printf ("8 adress - physical adress to logical\n");
                printf ("9 - quit\n");
                printf ("10 - graphviz\n");
                printf ("11 - linearization\n");

    while (!scanf_check(scanf("%d", &command)));

    while (command != 0) {
        switch (command) {
            case 1:
                if (!scanf_check (scanf (TYPE_SPECIFICATOR, &push_value))) {
                    break;
                }

                if (!scanf_check (scanf ("%d", &index))) {
                    break;
                }


                list_insert_before (&myList, push_value, index);
                break;

            case 2:
                if (!scanf_check (scanf (TYPE_SPECIFICATOR, &push_value))) {
                    break;
                }

                if (!scanf_check (scanf ("%d", &index))) {
                    break;
                }


                list_insert_after (&myList, push_value, index);
                break;

            case 3:
                if (!scanf_check (scanf (TYPE_SPECIFICATOR, &search_value))) {
                    break;
                }

                printf ("index of ");
                printf (TYPE_SPECIFICATOR, search_value);
                printf (" is %d\n",list_search (&myList, search_value));
                break;

            case 4:
                if (!scanf_check (scanf ("%d", &index))) {
                    break;
                }

                list_delete (&myList, index);
                break;

            case 5:
                list_dump (&myList);
                break;

            case 6:
                printf ("henlo, it's menu for list\n");
                printf ("1 num index - push before, enter first you must use 2 num 0\n");
                printf ("2 num index - push after\n");
                printf ("3 - list search\n");
                printf ("4 - list delete\n");
                printf ("5 - list dump\n");
                printf ("6 - menu\n");
                printf ("7 index - logical adress to physical\n");
                printf ("8 adress - physical adress to logical\n");
                printf ("9 - quit\n");
                printf ("10 - graphviz\n");
                printf ("11 - linearization\n");
                break;

            case 7:
                if (!scanf_check (scanf ("%d", &index))) {
                    break;
                }

                printf ("%d\n", list_log_in_phys (&myList, index));
                break;

            case 8:
                if (!scanf_check (scanf ("%d", &index))) {
                    break;
                }
                printf ("%d\n", list_phys_in_log (&myList, index));
                break;

            case 9:
                list_dtor (&myList);
                return 0;
                break;

            case 10:
                graph_dump (&myList);
                break;
                
            case 11:
                list_linearization (&myList);
                break;

            default:
                printf ("Undefined command\n");
                break;
        }
        
        while (!scanf_check(scanf("%d", &command)));

        if (list_check (&myList) != 0) {
            list_dtor (&myList);
            break;
        }
    }

    return 0;
}