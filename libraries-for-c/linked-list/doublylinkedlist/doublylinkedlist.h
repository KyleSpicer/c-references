#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

struct list {
	struct list *prev;
	struct list *next;
	int data;
};

typedef struct list list;

int size(list *);
void print(list *);
list *create_node(int);
list *get_node_at(list *, int);
void insert_front(list **, list *);
void insert_back(list *, list *);
void insert_at(list **, list *, int);
void delete_at(list **, int);
void delete_node(list **, list *);
void delete(list **);

#endif
