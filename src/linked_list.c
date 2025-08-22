#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node_At_Beginning(Node **head , int data) {
    Node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

void append_node_At_End(Node **head , int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void append_node_At_Position(Node **head , int data , int position) {
    if (position == 0) {
        append_node_At_Beginning(head, data);
        return;
    }
    Node *new_node = create_node(data);
    Node *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(new_node);
        return;
    }
    new_node->next = temp->next;
    temp->next = new_node;
}

int delete_node_At_Beginning(Node **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    Node *temp = *head;
    int data = temp->data;
    *head = (*head)->next;
    free(temp);
    return data;
}

int delete_node_At_End(Node **head) {
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
    Node *temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    int data = temp->next->data;
    free(temp->next);
    temp->next = NULL;
    return data;
}

int delete_node_At_Position(Node **head , int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    if (position == 0) {
        return delete_node_At_Beginning(head);
    }
    Node *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return -1;
    }
    Node *node_to_delete = temp->next;
    int data = node_to_delete->data;
    temp->next = node_to_delete->next;
    free(node_to_delete);
    return data;
}


int search_node(Node *head , int key) {
    Node *temp = head;
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


int size_of_linked_list(Node *head) {
    Node *temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}



int free_linked_list(Node **head) {
    if (*head == NULL) return -1;
    Node *temp = *head;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    return 0;
}



void print_linked_list(Node *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node *temp = head;
    printf("Linked list elements: [ ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("]\n");
}

