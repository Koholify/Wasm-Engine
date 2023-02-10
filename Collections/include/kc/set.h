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

kc_set kc_set_init(size_t len);
kc_strset kc_strset_init(size_t len);

void kc_set_free(kc_set t);
void kc_strset_free(kc_strset t);

size_t kc_set_len(kc_set t);
size_t kc_set_cap(kc_set t);
size_t kc_strset_len(kc_strset t);
size_t kc_strset_cap(kc_strset t);

int_hash kc_set_hash(kc_set t);
str_hash kc_strset_hash(kc_strset t);

bool kc_set_has(kc_set set, size_t val);
void kc_set_set(kc_set * set, size_t val);
void kc_set_remove(kc_set set, size_t val);
bool kc_strset_has(kc_strset set, const char* val);
void kc_strset_set(kc_strset * set, const char* val);
void kc_strset_remove(kc_strset set, const char* val);

kc_set kc_set_union(kc_set a, kc_set b);
kc_set kc_set_intersect(kc_set a, kc_set b);
kc_set kc_set_difference(kc_set a, kc_set b);
kc_strset kc_strset_union(kc_strset a, kc_strset b);
kc_strset kc_strset_intersect(kc_strset a, kc_strset b);
kc_strset kc_strset_difference(kc_strset a, kc_strset b);

typedef struct kc_set_iterator {
	size_t index;
	kc_set set;
} kc_set_iterator;

kc_set_iterator kc_set_iter(kc_set a);
bool kc_set_next(kc_set_iterator* it, size_t* next);

typedef struct kc_strset_iterator {
	size_t index;
	kc_strset set;
} kc_strset_iterator;

kc_strset_iterator kc_strset_iter(kc_strset a);
bool kc_strset_next(kc_strset_iterator* it, const char** next);

#endif
