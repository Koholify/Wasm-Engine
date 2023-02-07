#ifndef _KC_SET_H
#define _KC_SET_H

#include <stddef.h>
#include <stdbool.h>
#include "kc/array.h"

typedef size_t(*int_hash)(size_t);

typedef struct kc_set_item {
	bool is_used;
	size_t item;
} kc_set_item;

typedef struct kc_set {
	kc_set_item* data;
} kc_set;

size_t kc_set_defaultHash(size_t in);
kc_set kc_set_init(size_t len);
size_t kc_set_len(kc_set t);
size_t kc_set_cap(kc_set t);
int_hash kc_set_hash(kc_set t);

bool kc_set_has(kc_set set, size_t val);
void kc_set_set(kc_set * set, size_t val);

#endif
