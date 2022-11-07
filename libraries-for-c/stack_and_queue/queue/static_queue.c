#include "static_queue.h"

#include <stdio.h>
#include <stdlib.h>

//This a First - In First - Out(FIFO) data structure.
//
//Items are extracted from the front and new items can only be added to the
// back.
//
//The front pointer points to the next item to be extracted.
//
//The back pointer points to the position after the last item in the queue.
//
//Both front and back pointers can only move forward but move independently.
//
//The front pointer chases the back pointer but neither can overtake the other.
// ------------------------------------------------------------------------------
//------------------------------------------------------------------------------
queue * create_queue(int size)
{
	//Allocate one more space than the requested capacity because the back
	// pointer points to the position after the last item.
	queue * q = (queue *) malloc(sizeof(queue));
	q->capacity = size;
	q->data = (int *)malloc(sizeof(int) * (q->capacity + 1));
	q->front = q->data;
	q->back = q->data;
	return q;
}

void delete_queue(queue ** q)
{
	free((*q)->data);
	free(*q);
	*q = 0;
}

void reset(queue * q)
{
	q->front = q->data;
	q->back = q->data;
}

void insert(queue * q, int data)
{
	//Add to the queue then move the back pointer forward.
	//
	//The back pointer always points to the slot after the last item on the
	// queue.
	if (q->back != &q->data[q->capacity]) {
		//Insert then move forward.
		* (q->back)++ = data;
	} else {
		printf("Queue of size %d is full!\n", q->capacity);
	}
}

int extract(queue * q)
{
	//Move front pointer forward.
	if (q->front != q->back) {
		//Extract then move forward.
		++ (q->front);
		return *(q->front - 1);
	} else {
		printf("Queue is empty!\n");
		return *(q->front);
	}
}

int front(queue * q)
{
	return *(q->front);
}

int empty(queue * q)
{
	return (q->front == q->back);
}
