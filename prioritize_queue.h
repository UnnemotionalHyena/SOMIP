#ifndef PRIORITIZE_QUEUE_H_
#define PRIORITIZE_QUEUE_H_

typedef struct
{
    int priority;
    struct Order *data;
} node_t;

typedef struct
{
    node_t *nodes;
    int len;
    int size;
} heap_t;

void prioritize_push (heap_t *h, int priority,struct Order *data);
struct Order *prioritize_pop (heap_t *h);

#endif