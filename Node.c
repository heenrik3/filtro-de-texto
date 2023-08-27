#include "Node.h"

#include <stdlib.h>

Node* new_node(void* data)
{
    Node *node = malloc(sizeof(Node));
    if ( !node ) exit(1);

    node->data = data;
    node->next = node->ant = NULL;

    return node;
}
