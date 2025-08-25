#ifndef HASH_MAP_H
#define HASH_MAP_H

typedef struct {
    int key;
    int value;
} Entry;

typedef struct EntryNode {
    Entry entry;
    struct EntryNode *next;
} EntryNode;

typedef struct {
    EntryNode **buckets;
    int size;
    int capacity;
} HashMap;

HashMap *create_hash_map(int capacity);
int hash_map_put(HashMap *map, int key, int value);
int hash_map_get(HashMap *map, int key, int *value);
int hash_map_remove(HashMap *map, int key);
int hash_map_contains_key(HashMap *map, int key);
int hash_map_size(HashMap *map);
void hash_map_free(HashMap **map);
void hash_map_print(HashMap *map);

#endif