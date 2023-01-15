#include "kc/array.h"
#include <stdlib.h>

void * kc_arr_grow(void * a, size_t size, size_t cap) {
	if (!a) {
		kc_array_header * header = malloc(sizeof(kc_array_header) + (size * cap));
		header->size = size;
		header->length = 0;
		header->capacity = cap;
		return header + 1;
	}

	kc_array_header * header = kc_arr_header(a);
	size_t length = header->length;
	kc_array_header * temp = realloc(header, sizeof(kc_array_header) + (size * cap));

	temp->size = size;
	temp->length = length < cap ? length : cap;
	temp->capacity = cap;
	
	return temp + 1;
}

void kc_arr_free(void *a) {
	kc_array_header * header = kc_arr_header(a);
	free(header);
}

