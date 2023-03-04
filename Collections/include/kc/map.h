
#ifndef _KC_MAP_H
#define _KC_MAP_H

#include <stddef.h>
#include <stdbool.h>
#include "kc/array.h"

typedef size_t(*int_hash)(size_t);
typedef size_t(*str_hash)(const char*);

typedef struct kc_map_item {
	bool is_used;
	size_t key;
	void* value;
} kc_map_item;

typedef struct kc_strmap_item {
	bool is_used;
	char key[32];
	void* value;
} kc_strmap_item;

typedef struct kc_map {
	kc_map_item* data;
} kc_map;

typedef struct kc_strmap {
	kc_strmap_item * data;
} kc_strmap;

// Initialize set of unsigned int (len: Capacity)
kc_map kc_map_init(size_t len);
// Initialize map of strings (len: Capacity)
kc_strmap kc_strmap_init(size_t len);

// Deallocate map
void kc_map_free(kc_map t);
// Deallocate string map
void kc_strmap_free(kc_strmap t);

// Get length of map
size_t kc_map_len(kc_map t);
//Get capacity of map
size_t kc_map_cap(kc_map t);
// Get length of string map
size_t kc_strmap_len(kc_strmap t);
//Get capacity of string map
size_t kc_strmap_cap(kc_strmap t);

// Get hash for size_t
int_hash kc_map_hash();
// Get hash for string
str_hash kc_strmap_hash();

// Get if map contains value
bool kc_map_has(kc_map map, size_t val);
// Add element to map
void kc_map_set(kc_map * map, size_t key, void* val);
// Remove element from set
void kc_map_remove(kc_map map, size_t val);
// Copy a map to a new object
kc_map kc_map_copy(kc_map map);
// Retrieve value of key in map
void* kc_map_get(kc_map map, size_t val);

// Get if map contains value
bool kc_strmap_has(kc_strmap map, const char* val);
// Add element to map
void kc_strmap_set(kc_strmap * map, const char* key, void* val);
// Remove element from set
void kc_strmap_remove(kc_strmap map, const char* val);
// Copy a map to a new object
kc_strmap kc_strmap_copy(kc_strmap map);
// Retrieve value of key in map
void* kc_strmap_get(kc_strmap map, const char* val);

typedef struct kc_map_iterator {
	size_t index;
	kc_map map;
} kc_map_iterator;

// Create iterator for map
kc_map_iterator kc_map_iter(kc_map a);
// Returns true if value is map in next. False if complete.
bool kc_map_next(kc_map_iterator* it, kc_map_item** next);
void kc_map_foreach(kc_map map, void* data, void (*fn)(kc_map_item*, void*));

typedef struct kc_strmap_iterator {
	size_t index;
	kc_strmap map;
} kc_strmap_iterator;

// Create iterator for map
kc_strmap_iterator kc_strmap_iter(kc_strmap a);
// Returns true if value is map in next. False if complete.
bool kc_strmap_next(kc_strmap_iterator* it, kc_strmap_item** next);
void kc_strmap_foreach(kc_strmap map, void* data, void (*fn)(kc_strmap_item*, void*));

#endif
