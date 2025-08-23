#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

DNode *create_dnode(int data) {
    DNode *new_node = (DNode *)malloc(sizeof(DNode));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void append_dnode_at_beginning(DNode **head, int data) {
    DNode *new_node = create_dnode(data);
    if (*head != NULL) {
        new_node->next = *head;
        (*head)->prev = new_node;
    }
    *head = new_node;
}

void append_dnode_at_end(DNode **head, int data) {
    DNode *new_node = create_dnode(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    DNode *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

void append_dnode_at_position(DNode **head, int data, int position) {
    if (position == 0) {
        append_dnode_at_beginning(head, data);
        return;
    }
    DNode *new_node = create_dnode(data);
    DNode *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(new_node);
        return;
    }
    new_node->next = temp->next;
    new_node->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = new_node;
    }
    temp->next = new_node;
}

int delete_dnode_at_beginning(DNode **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    DNode *temp = *head;
    int data = temp->data;
    *head = temp->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
    return data;
}

int delete_dnode_at_end(DNode **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    if ((*head)->next == NULL) {
        int data = (*head)->data;
        free(*head);
        *head = NULL;
        return data;
    }
    DNode *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    int data = temp->data;
    temp->prev->next = NULL;
    free(temp);
    return data;
}

int delete_dnode_at_position(DNode **head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    if (position == 0) {
        return delete_dnode_at_beginning(head);
    }
    DNode *temp = *head;
    for (int i = 0; i < position && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds\n");
        return -1;
    }
    int data = temp->data;
    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    return data;
}

int search_dnode(DNode *head, int key) {
    DNode *temp = head;
    int position = 0;
    while (temp != NULL) {
        if (temp->data == key) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;
}

int size_of_doubly_linked_list(DNode *head) {
    DNode *temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int free_doubly_linked_list(DNode **head) {
    if (*head == NULL) return -1;
    DNode *temp = *head;
    while (temp != NULL) {
        DNode *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    return 0;
}

void print_doubly_linked_list(DNode *head) {
    if (head == NULL) {
        printf("Doubly linked list is empty\n");
        return;
    }
    DNode *temp = head;
    printf("Doubly linked list elements: [ ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("]\n");
}