/**
 * @file llist.h
 * @author Kyle Spicer
 * 
 * @brief
 *  
 * @date 2022-11-08
 */

#ifndef LLIST_H
#define LLIST_H

/**
 * @brief typedef for llist stuct - opaque type
 * 
 */
typedef struct llist_t llist_t;

/**
 * @brief calloc's size of one llist struct
 * 
 * @return llist_t* - pointer to llist that is ready for use
 */
llist_t * llist_create();

/**
 * @brief frees memory allocated for llist object
 * 
 * @param llist - llist you wish you destroy
 * @param destroy_data - function passed by user to destroy data (ex: free)
 */
void llist_destroy(llist_t ** llist, void (*destroy_data)(void *));

/**
 * @brief creates node and places node infront of data structure
 * 
 * @param llist - llist you'd like to populate
 * @param data - data for new element you want to insert
 * @return int - returns 0 on error or 1 on success
 */
int llist_insert_front(llist_t * llist, void * data);

/**
 * @brief creates node and places node at end of data structure
 * 
 * @param llist - llist you'd like to populate
 * @param data - data for new element you want to insert
 * @return int - returns 0 on error or 1 on success
 */
int llist_insert_back(llist_t * llist, void * data);

/**
 * @brief will print every element in a link list until NULL 
 * 
 * @param llist - llist you wish to reference
 * @param print_data - function for printing data
 */
void llist_print(llist_t * llist, void (*print_data)(void *));

/**
 * @brief removes first element from llist
 * 
 * @param p_llist - llist you'd like to extract head node from
 * @return void* 
 */
void * extract_head(llist_t * p_llist);

/**
 * @brief removes first element from llist
 * 
 * @param p_llist - llist you'd like to extract tail node from
 * @return void* 
 */
void * extract_tail(llist_t * p_llist);


/**
 * @brief push node to top of stack. Uses llist_insert_front function
 * 
 * @param p_stk - pointer to stack struct
 * @param data - data you'd like to push
 * @return int - return llist_insert_front(p_stk, data)
 */
int push(llist_t * p_stk, void * data);

/**
 * @brief pop node from top of stack
 * 
 * @param p_stk - pointer to stack struct
 * @return void* - return extract_head(p_stk)
 */
void * pop(llist_t * p_stk);

/**
 * @brief add to back of queue
 * 
 * @param llist - queue you'd like to add to 
 * @param data - data you'd like to add
 * @return int - return llist_insert_back(llist, data)
 */
int enqueue(llist_t * llist, void * data);

/**
 * @brief remove from front of queue
 * 
 * @param p_queue - queue you'd like to remove from
 * @return void* - return extract_head(p_queue)
 */
void * dequeue(llist_t * p_queue);

/**
 * @brief size of list, stack, queue
 * 
 * @param llist - structure you'd like the size of
 * @return int returns structure->count
 */
int list_size(llist_t * llist);

/**
 * @brief determines if any values are present
 * 
 * @param stack - struct to preview
 * @return int - return list->count
 */
int is_list_empty(struct llist_t* stack);

/**
 * @brief views first element in strucutre you pass
 * 
 * @param llist - strucutre you'd like to use
 * @return void* - return llist->head->data
 */
void * peek (llist_t * llist);

#endif /* LLIST_H */

/* end of file */
