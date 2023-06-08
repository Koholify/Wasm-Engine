#include "kc/array.h"
#include <stdio.h>
#include <stdlib.h>

void * kc_arr_grow(void * a, size_t size, size_t cap) {
	if (!a) {
		struct kc_array_header * header = (struct kc_array_header*)malloc(sizeof(struct kc_array_header) + (size * cap));
		header->length = 0;
		header->capacity = cap;
		return header + 1;
	}

	struct kc_array_header * header = kc_arr_header(a);
	size_t length = header->length;
	struct kc_array_header * temp = (struct kc_array_header*)realloc(header, sizeof(struct kc_array_header) + (size * cap));

	temp->length = length < cap ? length : cap;
	temp->capacity = cap;
	
	return temp + 1;
}

void kc_arr_free(void *a) {
	struct kc_array_header * header = kc_arr_header(a);
	free(header);
}

