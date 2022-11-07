#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct list {
	struct list *next;
	int data;
};

typedef struct list list;
int size(list *);
void print(list *);
list *create_node(int);
void insert_front(list **, list *);
void insert_back(list *, list *);
void insert_at(list **, list *, int);
void delete_at(list **, int);
void delete(list **);

#endif
