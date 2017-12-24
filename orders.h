#ifndef ORDERS_H_
#define ORDERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

struct Order
{
    struct Food *items;
    int items_size;
    int priority;
    int max_wait;
} Order;

struct Food
{
    int id;
    int preparation_time;
    int complexity;
    char cooking_apparatus[10];
} Food;

void initialize_foods(struct Food *menu);

#endif