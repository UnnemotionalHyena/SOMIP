#ifndef ORDERS_H_
#define ORDERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


struct Order 
{
    int items[4];
    int priority;
    int max_wait;
} Order;

struct Food 
{
    int id;
    int preparation_time;
    int complexity;
    // string cooking_apparatus;
} Food;

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

void initialize_foods(struct Food *menu);
void push (heap_t *h, int priority,struct Order *data);
struct Order *pop (heap_t *h);

#endif