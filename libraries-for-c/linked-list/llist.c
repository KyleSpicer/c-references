/**
 * @file llist.h
 * @author Kyle Spicer
 * 
 * @brief
 *  
 * @date 2022-11-08
 */

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
llist_destroy(llist_t **llist, void (*destroy_data)(void *))
{
    if (!llist)
    {
        return;
    }
    llist_t *p_llist = *llist;

    node_t * temp = p_llist->head;
    while (temp)
    {
        p_llist->head = temp->next;
        destroy_data(temp->data);
        free(temp);
        temp = p_llist->head;
    }

    free(*llist);
    *llist = NULL;
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
    return data;
}

/* push node to top of stack */
int push(llist_t * p_stk, void * data)
{
    return llist_insert_front(p_stk, data);
}

/* pop node from top of stack */
void * pop(llist_t * p_stk)
{
    return extract_head(p_stk);
}

/* add back -enqueue */
int enqueue(llist_t * llist, void * data)
{
    if(!llist || !data){
        return 0;
    }
    return llist_insert_back(llist, data);
}

/* remove front - dequeue */
void * dequeue(llist_t * p_queue)
{
    return extract_head(p_queue);
}

/* returns llist->count value */
int list_size(llist_t * llist)
{
    return llist->count;
}

/* peek head data */
void * peek (llist_t * llist)
{
    return llist->head->data;
}

int is_list_empty(struct llist_t* list)
{
	return list->count;
}
/* end of file */