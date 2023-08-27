#ifndef NODE_H
#define NODE_H

typedef struct _node Node;
struct _node
{
    void *data;
    Node *ant, *next;
};

Node* new_node(void* data);

#endif
