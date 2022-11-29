#ifndef LLIST_H
#define LLIST_H


typedef struct llist_t llist_t;

llist_t * llist_create();

void llist_destroy(llist_t * llist, void (*destroy_data)(void *));

int llist_insert_front(llist_t * llist, void * data);

int llist_insert_back(llist_t * llist, void * data);

void llist_print(llist_t * llist, void (*print_data)(void *));

void * extract_head(llist_t * p_llist);

void * extract_tail(llist_t * p_llist);

/* push node to top of stack */
int push(llist_t * p_stk, void * data);

/* pop node from top of stack */
void * pop(llist_t * p_stk);

/* add back -enqueue */
int enqueue(llist_t * llist, void * data);

/* remove front - dequeue */
void * dequeue(llist_t * p_queue);

/* size of list, stack, queue */
int list_size(llist_t * llist);

/* peek head data */
void * peek (llist_t * llist);

#endif /* LLIST_H */