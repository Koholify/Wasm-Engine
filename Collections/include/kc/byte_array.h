#ifndef _KC_BYTE_ARRAY_H
#define _KC_BYTE_ARRAY_H

#include <stddef.h>

typedef struct kc_byte_array {
    size_t typeSize;
    size_t size;
    void* data;
    size_t capacity;
} kc_byte_array;

size_t kc_bytes_getTypeSize(kc_byte_array* list);
kc_byte_array* kc_bytes_create(size_t capacity, size_t typeSize);
kc_byte_array* kc_bytes_create_default(size_t capacity, size_t typeSize);
void kc_bytes_add(kc_byte_array* list, void* item);
void kc_bytes_insert(kc_byte_array* list, void* item, size_t index);
void kc_bytes_removeAt(kc_byte_array* list, size_t index);
void kc_bytes_pop(kc_byte_array* list); 
void kc_bytes_free(kc_byte_array* list);
void kc_bytes_resize(kc_byte_array* list);

const void* kc_bytes_get(kc_byte_array* list, size_t index);
void kc_bytes_set(kc_byte_array* list, size_t index, const void* val);
size_t kc_bytes_length(kc_byte_array* list);
size_t kc_bytes_capacity(kc_byte_array* list);
void kc_bytes_clear(kc_byte_array* list);
int kc_bytes_isEmpty(kc_byte_array* list);

#endif

