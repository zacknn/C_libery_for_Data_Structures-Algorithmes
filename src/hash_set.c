#include <stdio.h>
#include <stdlib.h>
#include "hash_set.h"

#define INITIAL_CAPACITY 16

static int hash(int value, int capacity) {
    return abs(value) % capacity;
}

HashSet *create_hash_set(int capacity) {
    if (capacity <= 0) capacity = INITIAL_CAPACITY;
    HashSet *set = (HashSet *)malloc(sizeof(HashSet));
    set->buckets = (Node **)calloc(capacity, sizeof(Node *));
    set->size = 0;
    set->capacity = capacity;
    return set;
}

int hash_set_add(HashSet *set, int value) {
    int index = hash(value, set->capacity);
    Node *current = set->buckets[index];
    
    // Check if value already exists
    while (current != NULL) {
        if (current->data == value) return 0; // Value exists
        current = current->next;
    }
    
    // Add new value
    append_node_At_Beginning(&set->buckets[index], value);
    set->size++;
    return 1;
}

int hash_set_remove(HashSet *set, int value) {
    int index = hash(value, set->capacity);
    Node *current = set->buckets[index];
    int position = search_node(current, value);
    
    if (position == -1) return 0; // Value not found
    
    delete_node_At_Position(&set->buckets[index], position);
    set->size--;
    return 1;
}

int hash_set_contains(HashSet *set, int value) {
    int index = hash(value, set->capacity);
    return search_node(set->buckets[index], value) != -1;
}

int hash_set_size(HashSet *set) {
    return set->size;
}

void hash_set_free(HashSet **set) {
    if (*set == NULL) return;
    for (int i = 0; i < (*set)->capacity; i++) {
        free_linked_list(&(*set)->buckets[i]);
    }
    free((*set)->buckets);
    free(*set);
    *set = NULL;
}

void hash_set_print(HashSet *set) {
    if (set->size == 0) {
        printf("Hash set is empty\n");
        return;
    }
    printf("Hash set elements: [ ");
    for (int i = 0; i < set->capacity; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
    }
    printf("]\n");
}