#include <stdio.h>
#include <stdlib.h>
#include "circular_linked_list.h"

CNode *create_cnode(int data) {
    CNode *new_node = (CNode *)malloc(sizeof(CNode));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_cnode_at_beginning(CNode **head, int data) {
    CNode *new_node = create_cnode(data);
    if (*head == NULL) {
        *head = new_node;
        new_node->next = new_node;
        return;
    }
    CNode *last = *head;
    while (last->next != *head) {
        last = last->next;
    }
    new_node->next = *head;
    last->next = new_node;
    *head = new_node;
}

void append_cnode_at_end(CNode **head, int data) {
    CNode *new_node = create_cnode(data);
    if (*head == NULL) {
        *head = new_node;
        new_node->next = new_node;
        return;
    }
    CNode *last = *head;
    while (last->next != *head) {
        last = last->next;
    }
    last->next = new_node;
    new_node->next = *head;
}

void append_cnode_at_position(CNode **head, int data, int position) {
    if (position == 0) {
        append_cnode_at_beginning(head, data);
        return;
    }
    CNode *new_node = create_cnode(data);
    CNode *temp = *head;
    for (int i = 0; i < position - 1 && temp->next != *head; i++) {
        temp = temp->next;
    }
    if (temp->next == *head && position > size_of_circular_linked_list(*head)) {
        printf("Position out of bounds\n");
        free(new_node);
        return;
    }
    new_node->next = temp->next;
    temp->next = new_node;
}

int delete_cnode_at_beginning(CNode **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    CNode *temp = *head;
    int data = temp->data;
    if (temp->next == temp) {
        free(temp);
        *head = NULL;
        return data;
    }
    CNode *last = *head;
    while (last->next != *head) {
        last = last->next;
    }
    *head = temp->next;
    last->next = *head;
    free(temp);
    return data;
}

int delete_cnode_at_end(CNode **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    if ((*head)->next == *head) {
        int data = (*head)->data;
        free(*head);
        *head = NULL;
        return data;
    }
    CNode *temp = *head;
    CNode *prev = NULL;
    while (temp->next != *head) {
        prev = temp;
        temp = temp->next;
    }
    int data = temp->data;
    prev->next = *head;
    free(temp);
    return data;
}

int delete_cnode_at_position(CNode **head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    if (position == 0) {
        return delete_cnode_at_beginning(head);
    }
    CNode *temp = *head;
    CNode *prev = NULL;
    for (int i = 0; i < position && temp->next != *head; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (temp->next == *head && position >= size_of_circular_linked_list(*head)) {
        printf("Position out of bounds\n");
        return -1;
    }
    int data = temp->data;
    prev->next = temp->next;
    free(temp);
    return data;
}

int search_cnode(CNode *head, int key) {
    if (head == NULL) return -1;
    CNode *temp = head;
    int position = 0;
    do {
        if (temp->data == key) {
            return position;
        }
        temp = temp->next;
        position++;
    } while (temp != head);
    return -1;
}

int size_of_circular_linked_list(CNode *head) {
    if (head == NULL) return 0;
    CNode *temp = head;
    int count = 0;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    return count;
}

int free_circular_linked_list(CNode **head) {
    if (*head == NULL) return -1;
    CNode *temp = *head;
    CNode *first = *head;
    do {
        CNode *next = temp->next;
        free(temp);
        temp = next;
    } while (temp != first);
    *head = NULL;
    return 0;
}

void print_circular_linked_list(CNode *head) {
    if (head == NULL) {
        printf("Circular linked list is empty\n");
        return;
    }
    CNode *temp = head;
    printf("Circular linked list elements: [ ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("]\n");
}