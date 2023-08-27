#include <stdio.h>
#include <stdlib.h>

#include "List.h"

list* List()
{
    list *l = malloc(sizeof(list));
    if ( !l ) exit(1);

    l->length = 0;
    l->head = l->tail = NULL;

    return l;
}

void push_back(list* l, void* data)
{
    Node *new = new_node(data);

    if ( l->head )
    {
        new->ant = l->tail;
        l->tail = l->tail->next = new;
    }
    else
    {
        l->head = l->tail = new;
    }

    l->length++;
}

void* pop_back(list* l)
{
    void *data = l->tail->data;
    Node *tmp = l->tail;

    if (l->tail->ant)
    {
        l->tail = l->tail->ant;
        l->tail->next = NULL;
    }
    else
    {
        l->head = l->tail = NULL;
    }

    free(tmp);

    l->length--;

    return data;
}

void clear_list(list* l)
{
    while( !empty(l) ) free(pop_back(l));
}

int empty(list* l)
{
    return l->head ? 0 : 1;
}

int length(list* l)
{
    return l->length;
}

void extend(list* l, list* new_l)
{
    l->tail->next = new_l->head;
}

void* at(list* l, int position)
{
    Node *tmp = l->head;
    void* data = NULL;
    int c = 1;

    while( tmp )
    {
        if ( c == position )
        {
            data = tmp->data;
            break;
        }
        c++;
        tmp = tmp->next;
    }

    return data;
}

void* at_element(list* l, int position)
{
    Node *tmp = l->head;
    void* data = NULL;
    int c = 1;

    while( tmp )
    {
        if ( c == position )
        {
            data = tmp;
            break;
        }
        c++;
        tmp = tmp->next;
    }

    return data;
}

void* back(list* l)
{
    return at(l, length(l));
}

void  delete_at(list* l, int position)
{
    Node *tmp = l->head;
    int c = 1;

    while( tmp )
    {
        if ( c == position )
        {
            Node *ant = tmp->ant;
            Node *next = tmp->next;

            if ( position == 1 )
            {
                if (l->tail == l->head)
                {
                    l->head = l->tail = next;
                }
                else l->head = next;
            }
            else if ( position == length(l) )
            {
                l->tail = ant;
            }

            if (ant) ant->next = next;
            if (next) next->ant = ant;

            free(tmp);

            l->length--;

            break;
        }
        c++;
        tmp = tmp->next;
    }
}

void forEach(list *l, void (*callback)())
{
    for (Node *tmp = l->head; tmp; tmp = tmp->next) callback(tmp->data);
}

int indexOf(list *l, bool (*callback)(), void* arg)
{
    int index = 0, i = 1;

    for (Node *tmp = l->head; tmp; tmp = tmp->next)
    {
        if (callback(tmp->data, arg))
        {
            index = i;
            break;
        }

        i++;
    }

    return index;
}

bool some(list *l, bool (*callback)(), void* arg)
{
    Node *tmp = l->head;

    while ( tmp )
    {
        if (callback(tmp->data, arg)) return true;

        tmp = tmp->next;
    }

    return false;
}

bool every(list *l, bool (*callback)(), void* arg)
{
    Node *tmp = l->head;

    while ( tmp )
    {
        if (!callback(tmp->data, arg)) return false;

        tmp = tmp->next;
    }

    return true;
}

void* filter(list *l, bool (*callback)())
{
    list* n = List();

    Node *tmp = l->head;

    while ( tmp )
    {
        if ( callback(tmp->data) )
        {
            push_back(n, tmp->data);
        }

        tmp = tmp->next;
    }

    return n;
}

void sort_list(list *l, bool (*callback)())
{
    void (*swap)(Node*, Node*) = ({
        void __fn__(Node* item1, Node* item2)
        {
            void *tmp = item1->data;
            item1->data = item2->data;
            item2->data = tmp;
        } __fn__;
    });

    while(true)
    {
        Node *tmp = l->head;
        bool swapped = false;

        while( tmp && tmp->next )
        {
            if ( callback(tmp->data, tmp->next->data) )
            {
                swapped = true;

                swap(tmp, tmp->next);
            }

            tmp = tmp->next;
        }


        if (!swapped) break;
    }
}

////////////////////////////////////////////////////////////////////////

void print_list(list *l)
{

    int counter = 0;

    void (*print)(char *) =
        (
    {
        void __fn__ (char *item)
        {
            counter++;

            printf("'%s'%s", item, counter >= length(l) ? "" : ", ");

        }
        __fn__;
    });

    printf("[");

    if (length(l)) forEach(l, print);

    printf("]\n");
}
