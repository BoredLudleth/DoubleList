#ifndef LIST_HPP
#define LIST_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DBG printf("FILE:%s FUNC:%s LINE:%d\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);

typedef int type;
#define TYPE_SPECIFICATOR "%d"
#define TYPE_SPECIFICATOR_FIVE "%5d"
#define LIST_LENGTH 10
#define POISON 0xDEAD

struct elem {
    int prev  = 0;
    type data = POISON;
    int next  = 0;
};

struct spis {
    struct elem* list;

    FILE* output;

    int head;
    int length;
    int tail;

    int free;

    int errors;
};

enum Errors {
    NO_ERRORS    = 0,
    INSERT_ERROR = 1,
    DELETE_ERROR = 2,
    CONNECT_ERROR = 3
};

void list_ctor (struct spis* myList);

void list_dtor (struct spis* myList);

struct elem* list_log_in_phys (struct spis* myList, type index);

int list_phys_in_log (struct spis* myList, struct elem* Element);

void list_insert_before (struct spis* myList, type value, int index);

void list_insert_after (struct spis* myList, type value, int index);

int list_search (struct spis* myList, type value);

int list_delete (struct spis* myList, type index);

void list_dump (const struct spis*  myList);

int list_сheck (struct spis* myList);

char* inttoa(int n, char* s);

void reverse(char* s);

void graph_dump (struct spis* myList);

void list_linearization (struct spis* myList);

int scanf_check (int x);

#endif