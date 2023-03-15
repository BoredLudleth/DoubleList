#ifndef LIST_HPP
#define LIST_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

struct List {
    struct elem* list;

    FILE* output;
    FILE* log;

    int head;
    int length;
    int tail;

    int free;

    int errors = 0;
    int flag_linear;
};

enum Errors {
    NO_ERRORS    = 0,
    INSERT_ERROR = 1,
    DELETE_ERROR = 2,
    CONNECT_ERROR = 3
};

void list_ctor (struct List* myList);

void list_dtor (struct List* myList);

int list_log_in_phys (struct List* myList, int index);

int list_phys_in_log (struct List* myList, int index);

void list_first (struct List* myList, type value);

void list_last (struct List* myList, type value);

void list_insert_before (struct List* myList, type value, int index);

void list_insert_after (struct List* myList, type value, int index);

int list_search (struct List* myList, type value);

int list_delete (struct List* myList, type index);

int list_delete_first (struct List* myList);

int list_delete_last (struct List* myList);

void list_dump (const struct List*  myList);

int list_check (struct List* myList);

char* inttoa(int n, char* s);

void reverse(char* s);

void graph_dump (struct List* myList);

void list_linearization (struct List* myList);

int scanf_check (int x);

#endif