#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "linked_list.h"
#include "doubly_linked_list.h"
#include "circular_linked_list.h"

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

    // Singly Linked List tests
    Node* list = NULL;
    printf("\nSingly Linked List Test:\n");
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

    // Doubly Linked List tests
    DNode* dlist = NULL;
    printf("\nDoubly Linked List Test:\n");
    append_dnode_at_beginning(&dlist, 10);
    append_dnode_at_end(&dlist, 20);
    append_dnode_at_position(&dlist, 15, 1);
    print_doubly_linked_list(dlist);
    printf("Size of doubly linked list: %d\n", size_of_doubly_linked_list(dlist));
    printf("Position of 15: %d\n", search_dnode(dlist, 15));
    printf("Deleted from beginning: %d\n", delete_dnode_at_beginning(&dlist));
    print_doubly_linked_list(dlist);
    printf("Deleted from end: %d\n", delete_dnode_at_end(&dlist));
    print_doubly_linked_list(dlist);
    printf("Deleted from position 0: %d\n", delete_dnode_at_position(&dlist, 0));
    print_doubly_linked_list(dlist);
    printf("Is list empty? %d\n", dlist == NULL ? 1 : 0);
    free_doubly_linked_list(&dlist);
    printf("List freed, is empty? %d\n", dlist == NULL ? 1 : 0);

    // Circular Linked List tests
    CNode* clist = NULL;
    printf("\nCircular Linked List Test:\n");
    append_cnode_at_beginning(&clist, 10);
    append_cnode_at_end(&clist, 20);
    append_cnode_at_position(&clist, 15, 1);
    print_circular_linked_list(clist);
    printf("Size of circular linked list: %d\n", size_of_circular_linked_list(clist));
    printf("Position of 15: %d\n", search_cnode(clist, 15));
    printf("Deleted from beginning: %d\n", delete_cnode_at_beginning(&clist));
    print_circular_linked_list(clist);
    printf("Deleted from end: %d\n", delete_cnode_at_end(&clist));
    print_circular_linked_list(clist);
    printf("Deleted from position 0: %d\n", delete_cnode_at_position(&clist, 0));
    print_circular_linked_list(clist);
    printf("Is list empty? %d\n", clist == NULL ? 1 : 0);
    free_circular_linked_list(&clist);
    printf("List freed, is empty? %d\n", clist == NULL ? 1 : 0);

    return 0;
}