#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "kc/array.h"
#include "kc/set.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static void _set_item(kc_set set, size_t val, bool isNew);
static void _strset_item(kc_strset set, const char* val, bool isNew);

static size_t _set_get_hash(kc_set t, size_t val) {
	(void)t;
	int_hash hash = kc_set_hash();
	return hash(val);
}

static size_t _strset_get_hash(kc_strset t, const char* val) {
	(void)t;
	return kc_strset_hash()(val);
}

static kc_set_item* set_expand(kc_set set) {
	size_t newCap = kc_set_cap(set) * 2;
	kc_set temp = kc_set_init(newCap);
	for (size_t i = 0; i < kc_set_cap(set); i++) {
		if (set.data[i].is_used) {
			kc_set_set(&temp, set.data[i].item);
		}
	}

	kc_arr_free(set.data);
	return temp.data;
}

static kc_strset_item* strset_expand(kc_strset set) {
	size_t newCap = kc_strset_cap(set) * 2;
	kc_strset temp = kc_strset_init(newCap);
	for (size_t i = 0; i < kc_strset_cap(set); i++) {
		if (set.data[i].is_used) {
			kc_strset_set(&temp, set.data[i].item);
		}
	}

	kc_arr_free(set.data);
	return temp.data;
}

static void set_rehash(kc_set set, size_t start) {
	while (set.data[start].is_used) {
		set.data[start].is_used = false;
		_set_item(set, set.data[start].item, false);
		start++;
	}
}

static void strset_rehash(kc_strset set, size_t start) {
	while (set.data[start].is_used) {
		set.data[start].is_used = false;
		_strset_item(set, set.data[start].item, false);
		start++;
	}
}

size_t kc_int_hash(size_t x) {
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    x = x ^ (x >> 31);
    return x;
}

size_t kc_str_hash(const char* in) {
	size_t hash = (size_t)FNV_OFFSET;
	size_t len = strlen(in);
	for (size_t i = 0; i < len; i++) {
		hash = hash ^ in[i];
		hash = hash * FNV_PRIME;
	}
	return hash;
}

kc_set kc_set_init(size_t len) {
	kc_set set;
	set.data = NULL;
	kc_arr_setcap(set.data, len);
	memset(set.data, 0, sizeof(kc_set_item) * len);
	return set;
}

kc_strset kc_strset_init(size_t len) {
	kc_strset set;
	set.data = NULL;
	kc_arr_setcap(set.data, len);
	memset(set.data, 0, sizeof(kc_strset_item) * len);
	return set;
}

void kc_set_free(kc_set t) {
	kc_arr_free(t.data);
}
size_t kc_set_len(kc_set t) {
	return kc_arr_len(t.data);
}
size_t kc_set_cap(kc_set t) {
	return kc_arr_cap(t.data);
}

void kc_strset_free(kc_strset t) {
	kc_arr_free(t.data);
}
size_t kc_strset_len(kc_strset t) {
	return kc_arr_len(t.data);
}
size_t kc_strset_cap(kc_strset t) {
	return kc_arr_cap(t.data);
}

int_hash kc_set_hash() {
	return kc_int_hash;
}
str_hash kc_strset_hash() {
	return kc_str_hash;
}

int kc_set_getIndex(kc_set set, size_t val) {
	size_t i = _set_get_hash(set, val) % kc_set_cap(set);
	while (set.data[i].is_used) {
		if (set.data[i].item == val) return (int)i;
		if (++i >= kc_set_cap(set)) i = 0;
	}
	return -1;
}

bool kc_set_has(kc_set set, size_t val) {
	int i = kc_set_getIndex(set, val);
	return i >= 0;
}

static void _set_item(kc_set set, size_t val, bool isNew) {
	size_t i = _set_get_hash(set, val) % kc_set_cap(set);
	kc_set_item new = set.data[i];
	if(!new.is_used || (new.is_used && new.item == val)) {
		if (isNew && !new.is_used) {
			kc_arr_len(set.data)++;
		}

		new.is_used = true;
		new.item = val;
		set.data[i] = new;
	} else {
		while (set.data[i].is_used && set.data[i].item != val) {
			i++;
			if (i >= kc_set_cap(set)) {
				i = 0;
			}
		}

		if (isNew && !set.data[i].is_used) {
			kc_arr_len(set.data)++;
		}
		set.data[i].is_used = true;
		set.data[i].item = val;
	}
}

void kc_set_set(kc_set* set, size_t val) {
	if (kc_set_len(*set) > kc_set_cap(*set) * 0.75f) {
		set->data = set_expand(*set);
	}
	_set_item(*set, val, true);
}

void kc_set_remove(kc_set set, size_t val) {
	size_t cap = kc_set_cap(set);
	size_t i = _set_get_hash(set, val) % cap;
	while(set.data[i].is_used && set.data[i].item != val) {
		i++;
	}
	
	if (set.data[i].is_used && set.data[i].item == val) {
		set.data[i].is_used = false;
		kc_arr_len(set.data)--;
		size_t start = (i + 1) % cap;
		set_rehash(set, start);
	}
}

kc_set kc_set_copy(kc_set set) {
	kc_set new = kc_set_init(kc_set_cap(set));
	kc_set_iterator it = kc_set_iter(set);
	size_t val;
	while (kc_set_next(&it, &val))
		kc_set_set(&new, val);
	return new;
}

kc_set kc_set_union(kc_set a, kc_set b) {
	kc_set un = kc_set_init(kc_set_cap(a) + kc_set_cap(b));
	kc_set_iterator it = kc_set_iter(a);
	size_t val;
	while (kc_set_next(&it, &val)) {
		kc_set_set(&un, val);
	}

	it = kc_set_iter(b);
	while (kc_set_next(&it, &val)) {
		kc_set_set(&un, val);
	}

	return un;
}

kc_set kc_set_intersect(kc_set a, kc_set b) {
	size_t ca = kc_set_cap(a);
	size_t cb = kc_set_cap(b);
	kc_set in = kc_set_init(ca < cb ? cb : ca);

	kc_set m = ca < cb ? a : b;
	kc_set o = ca < cb ? b : a;
	kc_set_iterator it = kc_set_iter(m);
	size_t val;
	while (kc_set_next(&it, &val)) {
		if (kc_set_has(o, val)) {
			kc_set_set(&in, val);
		}
	}

	return in;
}

kc_set kc_set_difference(kc_set a, kc_set b) {
	size_t ca = kc_set_cap(a);
	size_t cb = kc_set_cap(b);
	kc_set diff = kc_set_init(ca + cb);

	size_t val;
	kc_set_iterator it = kc_set_iter(a);
	while (kc_set_next(&it, &val)) {
		if (!kc_set_has(b, val)) {
			kc_set_set(&diff, val);
		}
	}

	it = kc_set_iter(b);
	while (kc_set_next(&it, &val)) {
		if (!kc_set_has(a, val)) {
			kc_set_set(&diff, val);
		}
	}

	return diff;
}

bool kc_set_equals(kc_set a, kc_set b) {
	if (kc_set_len(a) != kc_set_len(b)) return false;
	kc_set_iterator it = kc_set_iter(a);
	size_t val;
	while (kc_set_next(&it, &val))
		if (!kc_set_has(b, val)) return false;
	return true;
}

bool kc_set_sub(kc_set a, kc_set b) {
	kc_set inter = kc_set_intersect(a, b);
	bool sub = kc_set_equals(inter, a);
	kc_set_free(inter);
	return sub;
}

kc_set_iterator kc_set_iter(kc_set a) {
	kc_set_iterator it;
	it.index = 0;
	it.set = a;
	return it;
}
bool kc_set_next(kc_set_iterator* it, size_t* next) {
	while (!(it->index > kc_set_cap(it->set)) && !it->set.data[it->index].is_used) {
		it->index++;
	}

	if (it->index < kc_set_cap(it->set)) {
		*next = it->set.data[it->index++].item;
		return true;
	}
	return false;
}

void kc_set_foreach(kc_set set, void* data, void (*fn)(size_t, void*)) {
	size_t val;
	kc_set_iterator it = kc_set_iter(set);
	while (kc_set_next(&it, &val))
		fn(val, data);
}


int kc_strset_getIndex(kc_strset set, const char* val) {
	size_t i = _strset_get_hash(set, val) % kc_strset_cap(set);
	while (set.data[i].is_used) {
		if (!strncmp(set.data[i].item, val, 31)) return (int)i;
		if (++i >= kc_strset_cap(set)) i = 0;
	}
	return -1;
}

bool kc_strset_has(kc_strset set, const char* val) {
	int i = kc_strset_getIndex(set, val);
	return i >= 0;
}

static void _strset_item(kc_strset set, const char* val, bool isNew) {
	size_t i = _strset_get_hash(set, val) % kc_strset_cap(set);
	kc_strset_item new = set.data[i];
	if(!new.is_used || (new.is_used && !strncmp(new.item, val, STR_HASH_LENGTH))) {
		if (isNew && !new.is_used) {
			kc_arr_len(set.data)++;
		}

		set.data[i].is_used = true;
		strncpy(set.data[i].item, val, STR_HASH_LENGTH);
	} else {
		while (set.data[i].is_used && strncmp(set.data[i].item, val, STR_HASH_LENGTH)) {
			i++;
			if (i >= kc_strset_cap(set)) {
				i = 0;
			}
		}

		if (isNew && !set.data[i].is_used) {
			kc_arr_len(set.data)++;
		}
		set.data[i].is_used = true;
		strncpy(set.data[i].item, val, STR_HASH_LENGTH);
	}
}

void kc_strset_set(kc_strset * set, const char* val) {
	if (kc_strset_len(*set) > kc_strset_cap(*set) * 0.75f) {
		set->data = strset_expand(*set);
	}
	_strset_item(*set, val, true);
}

void kc_strset_remove(kc_strset set, const char* val) {
	size_t cap = kc_strset_cap(set);
	size_t i = _strset_get_hash(set, val) % cap;
	while(set.data[i].is_used && strncmp(set.data[i].item, val, STR_HASH_LENGTH)) {
		i++;
	}
	
	if (set.data[i].is_used && !strncmp(set.data[i].item, val, STR_HASH_LENGTH)) {
		set.data[i].is_used = false;
		kc_arr_len(set.data)--;
		size_t start = (i + 1) % cap;
		strset_rehash(set, start);
	}
}

kc_strset kc_strset_copy(kc_strset set) {
	kc_strset new = kc_strset_init(kc_strset_cap(set));
	kc_strset_iterator it = kc_strset_iter(set);
	const char* val;
	while (kc_strset_next(&it, &val))
		kc_strset_set(&new, val);
	return new;
}

kc_strset kc_strset_union(kc_strset a, kc_strset b) {
	size_t newCap = kc_strset_cap(a) < kc_strset_cap(b) ? kc_strset_cap(b) : kc_strset_cap(a);
	kc_strset un = kc_strset_init(newCap);
	kc_strset_iterator it = kc_strset_iter(a);
	const char* val;
	while (kc_strset_next(&it, &val)) {
		kc_strset_set(&un, val);
	}

	it = kc_strset_iter(b);
	while (kc_strset_next(&it, &val)) {
		kc_strset_set(&un, val);
	}

	return un;
}

kc_strset kc_strset_intersect(kc_strset a, kc_strset b) {
	size_t ca = kc_strset_cap(a);
	size_t cb = kc_strset_cap(b);
	kc_strset in = kc_strset_init(ca < cb ? cb : ca);

	kc_strset m = ca < cb ? a : b;
	kc_strset o = ca < cb ? b : a;
	kc_strset_iterator it = kc_strset_iter(m);
	const char* val;
	while (kc_strset_next(&it, &val)) {
		if (kc_strset_has(o, val)) {
			kc_strset_set(&in, val);
		}
	}

	return in;
}

kc_strset kc_strset_difference(kc_strset a, kc_strset b) {
	size_t ca = kc_strset_cap(a);
	size_t cb = kc_strset_cap(b);
	kc_strset diff = kc_strset_init(ca < cb ? cb : ca);

	const char* val;
	kc_strset_iterator it = kc_strset_iter(a);
	while (kc_strset_next(&it, &val)) {
		if (!kc_strset_has(b, val)) {
			kc_strset_set(&diff, val);
		}
	}

	it = kc_strset_iter(b);
	while (kc_strset_next(&it, &val)) {
		if (!kc_strset_has(a, val)) {
			kc_strset_set(&diff, val);
		}
	}

	return diff;
}

bool kc_strset_equals(kc_strset a, kc_strset b) {
	if (kc_strset_len(a) != kc_strset_len(b)) return false;
	kc_strset_iterator it = kc_strset_iter(a);
	const char* val;
	while (kc_strset_next(&it, &val))
		if (!kc_strset_has(b, val)) return false;
	return true;
}

bool kc_strset_sub(kc_strset a, kc_strset b) {
	kc_strset inter = kc_strset_intersect(a, b);
	bool sub = kc_strset_equals(inter, a);
	kc_strset_free(inter);
	return sub;
}

kc_strset_iterator kc_strset_iter(kc_strset a) {
	kc_strset_iterator it;
	it.index = 0;
	it.set = a;
	return it;
}

bool kc_strset_next(kc_strset_iterator* it, const char** next) {
	while (it->index < kc_strset_cap(it->set) && !it->set.data[it->index].is_used) {
		it->index++;
	}

	if (it->index < kc_strset_cap(it->set)) {
		*next = it->set.data[it->index++].item;
		return true;
	}

	return false;
}

void kc_strset_foreach(kc_strset set, void* data, void (*fn)(const char*, void*)) {
	const char* val;
	kc_strset_iterator it = kc_strset_iter(set);
	while (kc_strset_next(&it, &val))
		fn(val, data);
}
