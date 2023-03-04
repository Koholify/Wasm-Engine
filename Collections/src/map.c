#include "kc/map.h"
#include "kc/set.h"
#include "kc/array.h"
#include <stdbool.h>

static void _set_item(kc_map map, size_t key, void* value, bool isNew);
static void _strset_item(kc_strmap map, const char* key, void* value, bool isNew);

static size_t _map_get_hash(kc_map t, size_t val) {
	return kc_map_hash(t)(val);
}

static size_t _strmap_get_hash(kc_strmap t, const char* val) {
	return kc_strmap_hash(t)(val);
}

static kc_map_item* map_expand(kc_map map) {
	size_t newCap = kc_map_cap(map) * 2;
	kc_map temp = kc_map_init(newCap);
	for (size_t i = 0; i < kc_map_cap(map); i++) {
		if (map.data[i].is_used) {
			kc_map_set(&temp, map.data[i].key, map.data[i].value);
		}
	}

	kc_arr_free(map.data);
	return temp.data;
}

static kc_strmap_item* strmap_expand(kc_strmap map) {
	size_t newCap = kc_strmap_cap(map) * 2;
	kc_strmap temp = kc_strmap_init(newCap);
	for (size_t i = 0; i < kc_strmap_cap(map); i++) {
		if (map.data[i].is_used) {
			kc_strmap_set(&temp, map.data[i].key, map.data[i].value);
		}
	}

	kc_arr_free(map.data);
	return temp.data;
}

static void map_rehash(kc_map map, size_t start) {
	while (map.data[start].is_used) {
		map.data[start].is_used = false;
		_set_item(map, map.data[start].key, map.data[start].value, false);
		start++;
	}
}

static void strmap_rehash(kc_strmap map, size_t start) {
	while (map.data[start].is_used) {
		map.data[start].is_used = false;
		_strset_item(map, map.data[start].key, map.data[start].value, false);
		start++;
	}
}

kc_map kc_map_init(size_t len) {
	kc_map map;
	map.data = NULL;
	kc_arr_setcap(map.data, len);
	memset(map.data, 0, sizeof(kc_map_item) * len);
	return map;
}

kc_strmap kc_strmap_init(size_t len) {
	kc_strmap map;
	map.data = NULL;
	kc_arr_setcap(map.data, len);
	memset(map.data, 0, sizeof(kc_strmap_item) * len);
	return map;
}

void kc_map_free(kc_map t) {
	kc_arr_free(t.data);
}

void kc_strmap_free(kc_strmap t) {
	kc_arr_free(t.data);
}

size_t kc_map_len(kc_map t) {
	return kc_arr_len(t.data);
}
size_t kc_map_cap(kc_map t) {
	return kc_arr_cap(t.data);
}

size_t kc_strmap_len(kc_strmap t) {
	return kc_arr_len(t.data);
}
size_t kc_strmap_cap(kc_strmap t) {
	return kc_arr_cap(t.data);
}

int_hash kc_map_hash() {
	return kc_int_hash;
}
str_hash kc_strmap_hash() {
	return kc_str_hash;
}

bool kc_map_has(kc_map map, size_t val) {
	size_t i = _map_get_hash(map, val) % kc_map_cap(map);
	while (map.data[i].is_used) {
		if (map.data[i].key == val) return true;
		if (++i >= kc_map_cap(map)) i = 0;
	}
	return false;
}

static void _set_item(kc_map map, size_t key, void* value, bool isNew) {
	size_t i = _map_get_hash(map, key) % kc_map_cap(map);
	kc_map_item new = map.data[i];
	if(!new.is_used || (new.is_used && new.key == key)) {
		if (isNew && !new.is_used) {
			kc_arr_len(map.data)++;
		}

		new.is_used = true;
		new.key = key;
		new.value = value;
		map.data[i] = new;
	} else {
		while (map.data[i].is_used && map.data[i].key != key) {
			i++;
			if (i >= kc_map_cap(map)) {
				i = 0;
			}
		}

		if (isNew && !map.data[i].is_used) {
			kc_arr_len(map.data)++;
		}
		map.data[i].is_used = true;
		map.data[i].key = key;
		map.data[i].value = value;
	}
}

void kc_map_set(kc_map* map, size_t key, void* value) {
	if (kc_map_len(*map) > kc_map_cap(*map) * 0.75f) {
		map->data = map_expand(*map);
	}
	_set_item(*map, key, value, true);
}

void kc_map_remove(kc_map map, size_t val) {
	size_t cap = kc_map_cap(map);
	size_t i = _map_get_hash(map, val) % cap;
	while(map.data[i].is_used && map.data[i].key != val) {
		i++;
	}
	
	if (map.data[i].is_used && map.data[i].key == val) {
		map.data[i].is_used = false;
		kc_arr_len(map.data)--;
		size_t start = (i + 1) % cap;
		map_rehash(map, start);
	}
}

kc_map kc_map_copy(kc_map map) {
	kc_map new = kc_map_init(kc_map_cap(map));
	kc_map_iterator it = kc_map_iter(map);
	kc_map_item val;
	while (kc_map_next(&it, &val))
		kc_map_set(&new, val.key, val.value);
	return new;
}

bool kc_strmap_has(kc_strmap map, const char* val) {
	size_t i = _strmap_get_hash(map, val) % kc_strmap_cap(map);
	while (map.data[i].is_used) {
		if (!strncmp(map.data[i].key, val, 31)) return true;
		if (++i >= kc_strmap_cap(map)) i = 0;
	}
	return false;
}

static void _strset_item(kc_strmap map, const char* key, void* value, bool isNew) {
	size_t i = _strmap_get_hash(map, key) % kc_strmap_cap(map);
	kc_strmap_item new = map.data[i];
	if(!new.is_used || (new.is_used && !strncmp(new.key, key, STR_HASH_LENGTH))) {
		if (isNew && !new.is_used) {
			kc_arr_len(map.data)++;
		}

		map.data[i].is_used = true;
		strncpy(map.data[i].key, key, STR_HASH_LENGTH);
		map.data[i].value = value;
	} else {
		while (map.data[i].is_used && strncmp(map.data[i].key, key, STR_HASH_LENGTH)) {
			i++;
			if (i >= kc_strmap_cap(map)) {
				i = 0;
			}
		}

		if (isNew && !map.data[i].is_used) {
			kc_arr_len(map.data)++;
		}
		map.data[i].is_used = true;
		strncpy(map.data[i].key, key, STR_HASH_LENGTH);
		map.data[i].value = value;
	}
}

void kc_strmap_set(kc_strmap * map, const char* key, void* value) {
	if (kc_strmap_len(*map) > kc_strmap_cap(*map) * 0.75f) {
		map->data = strmap_expand(*map);
	}
	_strset_item(*map, key, value, true);
}

void kc_strmap_remove(kc_strmap map, const char* val) {
	size_t cap = kc_strmap_cap(map);
	size_t i = _strmap_get_hash(map, val) % cap;
	while(map.data[i].is_used && strncmp(map.data[i].key, val, STR_HASH_LENGTH)) {
		i++;
	}
	
	if (map.data[i].is_used && !strncmp(map.data[i].key, val, STR_HASH_LENGTH)) {
		map.data[i].is_used = false;
		kc_arr_len(map.data)--;
		size_t start = (i + 1) % cap;
		strmap_rehash(map, start);
	}
}

kc_strmap kc_strmap_copy(kc_strmap map) {
	kc_strmap new = kc_strmap_init(kc_strmap_cap(map));
	kc_strmap_iterator it = kc_strmap_iter(map);
	kc_strmap_item val;
	while (kc_strmap_next(&it, &val))
		kc_strmap_set(&new, val.key, val.value);
	return new;
}

kc_map_iterator kc_map_iter(kc_map a) {
	kc_map_iterator it;
	it.index = 0;
	it.map = a;
	return it;
}
bool kc_map_next(kc_map_iterator* it, kc_map_item* next) {
	while (!(it->index > kc_map_cap(it->map)) && !it->map.data[it->index].is_used) {
		it->index++;
	}

	if (it->index < kc_map_cap(it->map)) {
		*next = it->map.data[it->index++];
		return true;
	}
	return false;
}

void kc_map_foreach(kc_map map, void* data, void (*fn)(kc_map_item, void*)) {
	kc_map_item val;
	kc_map_iterator it = kc_map_iter(map);
	while (kc_map_next(&it, &val))
		fn(val, data);
}

kc_strmap_iterator kc_strmap_iter(kc_strmap a) {
	kc_strmap_iterator it;
	it.index = 0;
	it.map = a;
	return it;
}

bool kc_strmap_next(kc_strmap_iterator* it, kc_strmap_item* next) {
	while (it->index < kc_strmap_cap(it->map) && !it->map.data[it->index].is_used) {
		it->index++;
	}

	if (it->index < kc_strmap_cap(it->map)) {
		*next = it->map.data[it->index++];
		return true;
	}

	return false;
}

void kc_strmap_foreach(kc_strmap map, void* data, void (*fn)(kc_strmap_item, void*)) {
	kc_strmap_item val;
	kc_strmap_iterator it = kc_strmap_iter(map);
	while (kc_strmap_next(&it, &val))
		fn(val, data);
}
