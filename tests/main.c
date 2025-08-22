#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "linked_list.h"

int main() {
    // Stack tests
    Stack* s = create_stack(3);
    push(s, 10);
    push(s, 20);
    push(s, 30);
    print_stack(s);
    printf("Is empty? %d\n", stack_is_empty(s));
    free_stack(s);

    // Queue tests
    Queue* q = create_queue(3);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    print_queue(q);
    printf("Is empty? %d\n", queue_is_empty(q));
    free_queue(q);

    // Linked List tests
    Node* list = NULL;
    printf("\nLinked List Test:\n");
    append_node_At_Beginning(&list, 10);
    append_node_At_End(&list, 20);
    append_node_At_Position(&list, 15, 1);
    print_linked_list(list);
    printf("Size of linked list: %d\n", size_of_linked_list(list));
    printf("Position of 15: %d\n", search_node(list, 15));
    printf("Deleted from beginning: %d\n", delete_node_At_Beginning(&list));
    print_linked_list(list);
    printf("Deleted from end: %d\n", delete_node_At_End(&list));
    print_linked_list(list);
    printf("Deleted from position 0: %d\n", delete_node_At_Position(&list, 0));
    print_linked_list(list);
    printf("Is list empty? %d\n", list == NULL ? 1 : 0);
    free_linked_list(&list);
    printf("List freed, is empty? %d\n", list == NULL ? 1 : 0);

    return 0;
}