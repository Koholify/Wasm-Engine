#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "kc/array.h"
#include "kc/set.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static void _set_item(kc_set set, size_t val, bool isNew);

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

static size_t kc_int_hash(size_t x) {
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    x = x ^ (x >> 31);
    return x;
}

static size_t kc_str_hash(const char* in) {
	size_t hash = FNV_OFFSET;
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
	kc_arr_header(set.data)->hash = kc_int_hash;
	memset(set.data, 0, sizeof(kc_set_item) * len);
	return set;
}

kc_strset kc_sset_init(size_t len) {
	kc_strset set;
	set.data = NULL;
	kc_arr_setcap(set.data, len);
	kc_arr_header(set.data)->str_hash = kc_str_hash;
	memset(set.data, 0, sizeof(kc_set_item) * len);
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

int_hash kc_set_hash(kc_set t) {
	return kc_arr_header(t.data)->hash;
}

str_hash kc_strset_hash(kc_strset t) {
	return kc_arr_header(t.data)->str_hash;
}

bool kc_set_has(kc_set set, size_t val) {
	size_t i = _set_get_hash(set, val) % kc_set_cap(set);
	while (set.data[i].is_used) {
		if (set.data[i].item == val) {
			return true;
		}
		i++;
	}
	return false;
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
	if (kc_set_len(*set) > kc_set_cap(*set) / 2) {
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
