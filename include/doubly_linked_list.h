#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct DNode {
    int data;
    struct DNode *next;
    struct DNode *prev;
} DNode;

DNode *create_dnode(int data);
void append_dnode_at_beginning(DNode **head, int data);
void append_dnode_at_end(DNode **head, int data);
void append_dnode_at_position(DNode **head, int data, int position);
int delete_dnode_at_beginning(DNode **head);
int delete_dnode_at_end(DNode **head);
int delete_dnode_at_position(DNode **head, int position);
int search_dnode(DNode *head, int key);
int size_of_doubly_linked_list(DNode *head);
int free_doubly_linked_list(DNode **head);
void print_doubly_linked_list(DNode *head);

#endif