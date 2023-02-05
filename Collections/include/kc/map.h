#ifndef _KC_MAP_H
#define _KC_MAP_H

#include <stddef.h>
#include <stdlib.h>
#include "kc/array.h"

#define kc_map_header(t) (((struct kc_map_header *) t) - 1)
#define kc_map_hash(t) (kc_map_header(t)->hash)
#define kc_map_keys(t) (kc_map_header(t)->keys)
#define kc_map_init(t, h) (t = kc_map_create(sizeof(*t), 16, h))
#define kc_map_set(t, k, v) (kc_map_keys(t)[kc_map_hash(k)] = k, :ew)

struct kc_map_kv_pair {
	size_t key;
	void* value;
};

struct kc_map_header {
	size_t length;
	size_t* keys;
	size_t (*hash)(size_t); 
};

void * kc_map_create(size_t size, size_t cap, size_t (*hash)(size_t));

void * kc_map_grow(void * a, size_t size, size_t cap);

void kc_map_free(void *a);

#endif
