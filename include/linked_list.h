#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data);
void append_node_At_Beginning(Node **head, int data);
void append_node_At_End(Node **head, int data);
void append_node_At_Position(Node **head, int data, int position);
int delete_node_At_Beginning(Node **head);
int delete_node_At_End(Node **head);
int delete_node_At_Position(Node **head, int position);
int search_node(Node *head, int key);
int size_of_linked_list(Node *head);
int free_linked_list(Node **head);
void print_linked_list(Node *head);

#endif