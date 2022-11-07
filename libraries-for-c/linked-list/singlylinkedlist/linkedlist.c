#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

int size(list * l)
{
	int s = 0;
	while (l != 0) {
		l = l->next;
		++s;
	}
	return s;
}

void print(list * l)
{
	for (int i = 0; l != 0; ++i) {
		printf("node %d has value %d\n", i, l->data);
		l = l->next;
	}
}

list *create_node(int d)
{
	list *n = (list *) malloc(sizeof(list));
	n->next = 0;
	n->data = d;
	return n;
}

void insert_front(list ** l, list * n)
{
	n->next = *l;
	*l = n;
}

void insert_back(list * l, list * n)
{
	while (l->next != 0) {
		l = l->next;
	}
	l->next = n;
}

void insert_at(list ** l, list * n, int p)
{
	//Insert node n at position p using zero indexing.
	//
	//Displace node at p with new node n, thus node at p - 1 links to n which links
	// to the node that was previously at p.
	//
	//Getting to node at position p takes p steps.Advance through list for only
	// p - 1 steps so the p - 1 node can be linked to the inserted node.
	//
//NOTE:The new node can be inserted at the back by specifying the position
	// that includes the node.But inserting at the front requires special
	// handling.
	if (p == 0) {
		insert_front(l, n);
		return;
	}
	list *ll = *l;
	for (int i = 0; i < p - 1 && ll->next != 0; ++i) {
		ll = ll->next;
	}
	n->next = ll->next;
	ll->next = n;
}

void delete_at(list ** l, int p)
{
	//Remove node n at position p using zero indexing.
	//
	//Node at p - 1 now links to the node at p + 1.
	//
	//Getting to node at position p takes p steps.Advance through list for p
	// steps and save the p - 1 node so it can be linked to the p + 1 node.
	//
//NOTE:Deleting at the front requires special handling.
	if (p == 0) {
		list *t = (*l)->next;
		free(*l);
		*l = t;
		return;
	}
	list *ll = *l;
	list *t = 0;
	for (int i = 0; i < p && ll->next != 0; ++i) {
		t = ll;
		ll = ll->next;
	}
	t->next = ll->next;
	free(ll);
}

void delete(list ** l)
{
	list *n = *l;
	while (n != 0) {
		list *t = n;
		n = n->next;
		free(t);
	}
	*l = 0;
}
