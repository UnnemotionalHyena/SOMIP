#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdio.h>

struct QNode
{
    int key;
    int order;
    struct QNode *next;
}QNode;

struct Queue
{
    struct QNode *front, *rear;
}Queue;

struct QNode* newNode(int k, int or);
struct Queue *createQueue();
void enQueue(struct Queue *q, int k, int or);
struct QNode *deQueue(struct Queue *q);

#endif