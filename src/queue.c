#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *create_queue(int capacity) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->font = 0;
    queue->rear = -1;
    queue->data = (int *)malloc(capacity * sizeof(int));
    return queue;
}

void enqueue(Queue *queue, int value) {
    if (queue->rear == queue->capacity - 1) {
        printf("Queue overflow\n");
        return;
    }
    queue->data[++queue->rear] = value;
}


int dequeue(Queue *queue) {
    if (queue_is_empty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }
    return queue->data[queue->font++];
}

int peak(Queue *queue) {
    if (queue_is_empty(queue)) return -1;
    return queue->data[queue->font];
}

int queue_is_empty(Queue *queue) {
    return queue->font > queue->rear;
}

int size(Queue *queue) {
    return queue->rear - queue->font + 1;
}

int free_queue(Queue *queue) {
    if (queue == NULL) return -1;
    free(queue->data);
    free(queue);
    return 0;
}

void print_queue(Queue *queue) {
    if (queue_is_empty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: [ ");
    for (int i = queue->font; i <= queue->rear; i++) {
        printf("%d ", queue->data[i]);
    }
    printf(" ]\n");
}
