#ifndef QUEUE_H
#define QUEUE_H

typedef struct 
{
    int *data;
    int font;
    int rear;
    int capacity;
}Queue;

Queue *create_queue(int capacity);
void enqueue(Queue *queue , int value);
int dequeue(Queue *queue);
int peak(Queue *queue);
int queue_is_empty(Queue *queue);
int size(Queue *queue);
int free_queue(Queue *queue);

#endif
