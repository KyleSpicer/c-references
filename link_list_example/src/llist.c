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

/* will print every element in a link list until NULL */
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

void *
extract_head(llist_t * p_llist)
{
    void * data = NULL; // establishing default return val
    if (p_llist->head)
    {
        node_t * curr = p_llist->head;
        p_llist->head = curr->next;
        
        if(!p_llist->head)
        {
            p_llist->tail = p_llist->head; // sets tail to NULL if head was NULL
        }

        data = curr->data; // person struct data
        p_llist->count--; // decrements counter after removal of node
        free(curr); // free node
    
    }

    return data;
}

void *
extract_tail(llist_t * p_llist)
{
    void * data = NULL; // create default return val
    if(!p_llist || !p_llist->head)
        {
            return data;
        }


    node_t * temp = NULL;
    node_t * curr = p_llist->head;


    while(curr->next)
    {
        temp = curr;
        curr = curr->next;
    }

    p_llist->tail = temp;

    if(temp)
    {
        temp->next = NULL;
    }
    
    else
    {
        p_llist->head = NULL;
    }

    p_llist->count--;
    data = curr->data;
    free(curr);
    
    // if(!curr) // if empty
    // {
    //     return data; 
    // }

    // // while((curr->next != p_llist->tail) || (curr->next != NULL))
    // while(curr->next && curr->next->next)
    // {
    //     curr = curr->next;
    // }

    // temp = p_llist->tail;

    // if (!curr->next)
    // {
    //     p_llist->tail = NULL;
    //     p_llist->head = NULL;
    // }
    // else
    // {
    //     p_llist->tail = curr;
    //     curr->next = NULL;
    // }
    
    // data = temp->data;
    
    return data;
}

// int extract_from_back

/* end of file */


// add_to_end(node_t ** head, int data)
// add_after_target(node_t * head, int target, int data)
// add_before_target(node_t * head, int target, int data)
// extract_after(node_t * head, int target)
// extract_before(node_t * head, int target)
// peek function
