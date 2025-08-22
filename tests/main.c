#include <stdio.h>
#include "stack.h"
#include "queue.h"

int main() {
    Stack* s = create_stack(3);
    push(s, 10);
    push(s, 20);
    push(s, 30);
    print_stack(s);
    printf("Is empty? %d\n", stack_is_empty(s));
    free_stack(s);



    Queue* q = create_queue(3);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    print_queue(q);
    printf("Is empty? %d\n", queue_is_empty(q));
    free_queue(q);
    return 0;
}
