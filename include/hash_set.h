#ifndef HASH_SET_H
#define HASH_SET_H

#include "linked_list.h"

typedef struct {
    Node **buckets;
    int size;
    int capacity;
} HashSet;

HashSet *create_hash_set(int capacity);
int hash_set_add(HashSet *set, int value);
int hash_set_remove(HashSet *set, int value);
int hash_set_contains(HashSet *set, int value);
int hash_set_size(HashSet *set);
void hash_set_free(HashSet **set);
void hash_set_print(HashSet *set);

#endif

