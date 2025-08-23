#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

typedef struct CNode {
    int data;
    struct CNode *next;
} CNode;

CNode *create_cnode(int data);
void append_cnode_at_beginning(CNode **head, int data);
void append_cnode_at_end(CNode **head, int data);
void append_cnode_at_position(CNode **head, int data, int position);
int delete_cnode_at_beginning(CNode **head);
int delete_cnode_at_end(CNode **head);
int delete_cnode_at_position(CNode **head, int position);
int search_cnode(CNode *head, int key);
int size_of_circular_linked_list(CNode *head);
int free_circular_linked_list(CNode **head);
void print_circular_linked_list(CNode *head);

#endif