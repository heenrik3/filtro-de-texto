#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

#include "Node.h"

typedef struct _list {
        Node *head, *tail;
        int length;
}list;

list* List();
void  push_back(list* l, void* data);
void* pop_back(list* l);
void  clear_list(list* l);
int   empty(list* l);
int   length(list* l);
void  extend(list* l, list* new_l);
void* at(list* l, int position);
void* at_element(list* l, int position);
void* back(list* l);
void  delete_at(list* l, int position);
void  forEach(list*l, void (*callback)());
int   indexOf(list *l, bool (*callback)(), void* arg);
bool  some(list *l, bool (*callback)(), void* arg);
bool  every(list *l, bool (*callback)(), void* arg);
void* filter(list *l, bool (*callback)());
void  sort_list(list *l, bool (*callback)());

////////////////////////////////
void print_list(list* l);
#endif
