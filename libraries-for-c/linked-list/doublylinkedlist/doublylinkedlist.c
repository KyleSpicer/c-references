#include "doublylinkedlist.h"

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
	n->prev = 0;
	n->next = 0;
	n->data = d;
	return n;
}

list *get_node_at(list * l, int p)
{
	for (int i = 0; i < p; ++i) {
		l = l->next;
	}
	return l;
}

void insert_front(list ** l, list * n)
{
	n->prev = 0;
	n->next = *l;
	(*l)->prev = n;
	*l = n;
}

void insert_back(list * l, list * n)
{
	while (l->next != 0) {
		l = l->next;
	}
	l->next = n;
	n->prev = l;
	n->next = 0;
}

void insert_at(list ** l, list * n, int p)
{
	//Insert node n at position p using zero indexing.
	//
	//Displace node at p with new node n, thus node at p - 1 links to n which links
	// to the node that was previously at p.
	//
	//Getting to node at position p takes p steps.Advance through list for
	//p - 1 steps so the p - 1 node can be linked to the inserted node.
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
	if (ll->next == 0) {
		//Position exceeeded size of list; add new node to the end.
			ll->next = n;
		n->prev = ll;
		return;
	}
	n->next = ll->next;
	n->prev = ll;
	ll->next->prev = n;
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
		t->prev = 0;
		free(*l);
		*l = t;
		return;
	}
	list *ll = *l;
	for (int i = 0; i < p && ll->next != 0; ++i) {
		ll = ll->next;
	}
	list *t = ll->prev;
	list *u = ll->next;
	t->next = ll->next;
	if (u != 0) {
		u->prev = t;
	}
	free(ll);
}

void delete_node(list ** l, list * n)
{
	list *t = n->prev;
	list *u = n->next;
	//Test if at front or end of list.
		if (u != 0) {
			//Not at end.
			u->prev = t;
		}
	if (t != 0) {
		//Not at front.
		t->next = u;
	} else {
		//At front so new head pointer.
		* l = u;
	}
	free(n);
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
