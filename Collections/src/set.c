#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "kc/array.h"
#include "kc/set.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static size_t _set_get_hash(kc_set t, size_t val) {
	return kc_set_hash(t)(val);
}

static kc_set_item* set_expand(kc_set set) {
	size_t newCap = kc_set_cap(set) * 2;
	kc_set temp = kc_set_init(newCap);
	for (size_t i = 0; i < kc_set_cap(set); i++) {
		if (set.data[i].is_used) {
			kc_set_set(&temp, set.data[i].item);
		}
	}

	return temp.data;
}

size_t kc_set_defaultHash(size_t in) {
	size_t hash = FNV_OFFSET;
	hash = hash ^ in;
	hash = hash * FNV_PRIME;
	return hash;
}

kc_set kc_set_init(size_t len) {
	kc_set set = { 0 };
	set.data = NULL;
	kc_arr_setcap(set.data, len);
	kc_arr_header(set.data)->hash = kc_set_defaultHash;
	memset(set.data, 0, sizeof(kc_set_item) * len);
	return set;
}

size_t kc_set_len(kc_set t) {
	return kc_arr_len(t.data);
}

size_t kc_set_cap(kc_set t) {
	return kc_arr_cap(t.data);
}

int_hash kc_set_hash(kc_set t) {
	return kc_arr_header(t.data)->hash;
}

bool kc_set_has(kc_set set, size_t val) {
	size_t i = _set_get_hash(set, val);
	return set.data[i].is_used;
}

void kc_set_set(kc_set* set, size_t val) {
	if (kc_set_len(*set) > kc_set_cap(*set)) {
		set->data = set_expand(*set);
	}

	size_t i = _set_get_hash(*set, val);
	kc_set_item new = set->data[i];
	if(!new.is_used || (new.is_used && new.item == val)) {
		new.is_used = true;
		new.item = val;
		set->data[i] = new;
		kc_arr_len(set->data)++;
	} else {
		while (!set->data[i].is_used || (new.is_used && new.item == val)) {
			i++;
			if (i >= kc_set_cap(*set)) {
				i = 0;
			}
		}

		new.item = val;
		set->data[i] = new;
	}
}
