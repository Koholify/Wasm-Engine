#ifndef _KC_SET_H
#define _KC_SET_H

#include <stddef.h>
#include <stdbool.h>
#include "kc/array.h"

typedef size_t(*int_hash)(size_t);
typedef size_t(*str_hash)(const char*);

typedef struct kc_set_item {
	bool is_used;
	size_t item;
} kc_set_item;

typedef struct kc_strset_item {
	bool is_used;
	char item[32];
} kc_strset_item;

typedef struct kc_set {
	kc_set_item* data;
} kc_set;

typedef struct kc_strset {
	kc_strset_item * data;
} kc_strset;

// Initialize set of unsigned int (len: Capacity)
kc_set kc_set_init(size_t len);
// Initialize set of strings (len: Capacity)
kc_strset kc_strset_init(size_t len);

// Deallocate set
void kc_set_free(kc_set t);
// Deallocate string set
void kc_strset_free(kc_strset t);

// Get length of set
size_t kc_set_len(kc_set t);
//Get capacity of set
size_t kc_set_cap(kc_set t);
// Get length of string set
size_t kc_strset_len(kc_strset t);
//Get capacity of string set
size_t kc_strset_cap(kc_strset t);

// Get hash for size_t
int_hash kc_set_hash();
// Get hash for string
str_hash kc_strset_hash();

// Get index of element in set (-1 if not found)
int kc_set_getIndex(kc_set set, size_t val);
// Get if set contains value
bool kc_set_has(kc_set set, size_t val);
// Add element to set
void kc_set_set(kc_set * set, size_t val);
// Remove element from set
void kc_set_remove(kc_set set, size_t val);
// Copy a set to a new object
kc_set kc_set_copy(kc_set set);

// Get index of element in set (-1 if not found)
int kc_strset_getIndex(kc_strset set, const char* val);
// Get if set contains value
bool kc_strset_has(kc_strset set, const char* val);
// Add element to set
void kc_strset_set(kc_strset * set, const char* val);
// Remove element from set
void kc_strset_remove(kc_strset set, const char* val);
// Copy a set to a new object
kc_strset kc_strset_copy(kc_strset set);

// Create a new set containing all items from a and b
kc_set kc_set_union(kc_set a, kc_set b);
// Create new set containing matching items in a and b
kc_set kc_set_intersect(kc_set a, kc_set b);
// Create new set containing unique items in a and b
kc_set kc_set_difference(kc_set a, kc_set b);
// Return true if 2 sets are equal
bool kc_set_equals(kc_set a, kc_set b);

// Create a new set containing all items from a and b
kc_strset kc_strset_union(kc_strset a, kc_strset b);
// Create new set containing matching items in a and b
kc_strset kc_strset_intersect(kc_strset a, kc_strset b);
// Create new set containing unique items in a and b
kc_strset kc_strset_difference(kc_strset a, kc_strset b);
// Return true if 2 sets are equal
bool kc_strset_equals(kc_strset a, kc_strset b);

typedef struct kc_set_iterator {
	size_t index;
	kc_set set;
} kc_set_iterator;

// Create iterator for set
kc_set_iterator kc_set_iter(kc_set a);
// Returns true if value is set in next. False if complete.
bool kc_set_next(kc_set_iterator* it, size_t* next);

typedef struct kc_strset_iterator {
	size_t index;
	kc_strset set;
} kc_strset_iterator;

// Create iterator for set
kc_strset_iterator kc_strset_iter(kc_strset a);
// Returns true if value is set in next. False if complete.
bool kc_strset_next(kc_strset_iterator* it, const char** next);

#endif
