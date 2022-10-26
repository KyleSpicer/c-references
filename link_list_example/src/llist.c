#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

typedef struct node_t
{
    void *          data;
    struct node_t * next;
} node_t;

struct llist_t
{
    node_t * head;
    node_t * tail;
    uint64_t count;
};

static node_t * create_node(void * data);

llist_t *
llist_create()
{
    return calloc(1, sizeof(llist_t));
}

static node_t *
create_node(void * data)
{
    node_t * node = NULL;

    node = calloc(1, sizeof(*node));
    if (node)
    {
        node->data = data;
    }

    return node;
}

void
llist_destroy(llist_t * p_llist, void (*destroy_data)(void *))
{
    if (!p_llist)
    {
        return;
    }

    node_t * temp = p_llist->head;
    while (temp)
    {
        p_llist->head = temp->next;
        destroy_data(temp->data);
        free(temp);
        temp = p_llist->head;
    }

    free(p_llist);
}

int
llist_insert_front(llist_t * p_llist, void * data)
{
    int ret = 0;
    if (!p_llist || !data)
    {
        goto INSERT_FRONT;
    }

    node_t * node = create_node(data);
    if (!node)
    {
        goto INSERT_FRONT;
    }

    if (!p_llist->tail)
    {
        p_llist->tail = node;
    }

    node->next    = p_llist->head;
    p_llist->head = node;
    p_llist->count++;
    ret = 1;

INSERT_FRONT:
    return ret;
}

int
llist_insert_back(llist_t * p_llist, void * data)
{
    int ret = 0;
    if (!p_llist || !data)
    {
        goto INSERT_BACK;
    }

    node_t * node = create_node(data);
    if (!node)
    {
        goto INSERT_BACK;
    }

    if (p_llist->tail)
    {
        p_llist->tail->next = node;
        p_llist->tail       = node;
    }
    else
    {
        p_llist->head = node;
        p_llist->tail = node;
    }

    p_llist->count++;
    ret = 1;

INSERT_BACK:
    return ret;
}


/*  */
void
llist_print(llist_t * p_llist, void (*print_data)(void *))
{
    if (!p_llist)
    {
        return;
    }

    node_t * node = p_llist->head;
    while (node)
    {
        print_data(node->data);
        node = node->next;
    }
}