#include <stdio.h>
#include <stdlib.h>
#include "hash_map.h"

#define INITIAL_CAPACITY 16

static int hash(int key, int capacity) {
    return abs(key) % capacity;
}

static EntryNode *create_entry_node(int key, int value) {
    EntryNode *node = (EntryNode *)malloc(sizeof(EntryNode));
    node->entry.key = key;
    node->entry.value = value;
    node->next = NULL;
    return node;
}

HashMap *create_hash_map(int capacity) {
    if (capacity <= 0) capacity = INITIAL_CAPACITY;
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (EntryNode **)calloc(capacity, sizeof(EntryNode *));
    map->size = 0;
    map->capacity = capacity;
    return map;
}

int hash_map_put(HashMap *map, int key, int value) {
    int index = hash(key, map->capacity);
    EntryNode *current = map->buckets[index];
    
    // Check if key exists
    while (current != NULL) {
        if (current->entry.key == key) {
            current->entry.value = value; // Update value
            return 0;
        }
        current = current->next;
    }
    
    // Add new key-value pair
    EntryNode *new_node = create_entry_node(key, value);
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
    map->size++;
    return 1;
}

int hash_map_get(HashMap *map, int key, int *value) {
    int index = hash(key, map->capacity);
    EntryNode *current = map->buckets[index];
    
    while (current != NULL) {
        if (current->entry.key == key) {
            *value = current->entry.value;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int hash_map_remove(HashMap *map, int key) {
    int index = hash(key, map->capacity);
    EntryNode *current = map->buckets[index];
    EntryNode *prev = NULL;
    
    while (current != NULL) {
        if (current->entry.key == key) {
            if (prev == NULL) {
                map->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            map->size--;
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

int hash_map_contains_key(HashMap *map, int key) {
    int index = hash(key, map->capacity);
    EntryNode *current = map->buckets[index];
    
    while (current != NULL) {
        if (current->entry.key == key) return 1;
        current = current->next;
    }
    return 0;
}

int hash_map_size(HashMap *map) {
    return map->size;
}

void hash_map_free(HashMap **map) {
    if (*map == NULL) return;
    for (int i = 0; i < (*map)->capacity; i++) {
        EntryNode *current = (*map)->buckets[i];
        while (current != NULL) {
            EntryNode *next = current->next;
            free(current);
            current = next;
        }
    }
    free((*map)->buckets);
    free(*map);
    *map = NULL;
}

void hash_map_print(HashMap *map) {
    if (map->size == 0) {
        printf("Hash map is empty\n");
        return;
    }
    printf("Hash map elements: [ ");
    for (int i = 0; i < map->capacity; i++) {
        EntryNode *current = map->buckets[i];
        while (current != NULL) {
            printf("(%d:%d) ", current->entry.key, current->entry.value);
            current = current->next;
        }
    }
    printf("]\n");
}