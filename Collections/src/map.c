#include "kc/map.h"

void * kc_map_create(size_t size, size_t cap, size_t (*hash)(size_t)) {
	struct kc_map_header * header = malloc(sizeof(struct kc_map_header) + (cap * size));
	header->length = 0;
	header->keys = NULL;
	kc_arr_setlen(header->keys, cap);

	if (hash) {
		header->hash = hash;
	}

	return header + 1;
}

void * kc_map_grow(void * a, size_t size, size_t cap) {
	struct kc_map_header * header = kc_map_header(a);
	size_t length = header->length;
	struct kc_map_header * temp = realloc(header,
			sizeof(struct kc_map_header) + (size * cap));
	temp->length = length < cap ? length : cap;
	kc_arr_setlen(temp->keys, cap);

	return temp + 1;
}

void kc_map_free(void *a) {
	struct kc_map_header * header = kc_map_header(a);
	free(header);
}
