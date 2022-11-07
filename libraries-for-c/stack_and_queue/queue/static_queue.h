#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

struct queue {
	int *front;
	int *back;
	int *data;
	int capacity;
};
typedef struct queue queue;

queue *create_queue(int);
void delete_queue(queue **);
void insert(queue *, int);
int extract(queue *);
int front(queue *);
int empty(queue *);
void reset(queue *);

#endif
