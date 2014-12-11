#include <stdio.h>
#include "queue.h"

void initQueue(queue * inQueue)
{
    inQueue->head = -1;
    inQueue->tail = -1;
}

void enqueue(queue * inQueue, node * element)
{
    if (isFull(inQueue))
    {
        printf("Queue is full\n");
        return;
    }
    inQueue->contents[++inQueue->tail % MAXSIZE] = element;
}

node * dequeue(queue * inQueue)
{
    if (isEmpty(inQueue))
    {
        printf("Queue is empty\n");
        return NULL;
    }
    return inQueue->contents[++inQueue->head % MAXSIZE];
}

int isEmpty(queue * inQueue)
{
    return inQueue->head == inQueue->tail;
}

int isFull(queue * inQueue)
{
    return (inQueue->tail - MAXSIZE) == inQueue->head;
}
