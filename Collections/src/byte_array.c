#include "kc/byte_array.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <alloca.h>


static void increaseArraySize(kc_byte_array* list){
    int newCapacity = 8 + list->capacity;
    size_t dataSize = list->typeSize;
    void *newList = malloc(dataSize * newCapacity);
    if (!newList) {
        printf("Not enough memory!!\n");
        abort();
    }

    memcpy(newList, list->data, list->size * dataSize);

    free(list->data);
    list->data = newList;
    list->capacity = newCapacity;
}

size_t kc_bytes_getTypeSize(kc_byte_array* list) {
    return list->typeSize;
}

kc_byte_array* kc_bytes_create_default(size_t capacity, size_t typeSize)
{
	kc_byte_array* a = kc_bytes_create(capacity, typeSize);
	a->size = a->capacity;
	return a;
}

kc_byte_array* kc_bytes_create(size_t capacity, size_t typeSize) {    
    kc_byte_array* newList = malloc(sizeof(kc_byte_array));
    if (newList == NULL) {
        printf("Not Enough Memory available\n");
        abort();
    }

    newList->capacity = capacity;
    newList->size = 0;
    newList->typeSize = typeSize;
    newList->data = malloc(typeSize * capacity);
	memset(newList->data, 0, typeSize * capacity);
    if(newList->data == NULL) {
        printf("Not Enough Memory available\n");
        free(newList);
        abort();
    }

    return newList;
}

void kc_bytes_free(kc_byte_array* list) {
    free(list->data);
    free(list);
}

static void* _get(kc_byte_array* list, size_t index) {
    return (void*)(((char*)list->data) + (index * list->typeSize));
}

const void* kc_bytes_get(kc_byte_array* list, size_t index) {
    return _get(list, index);
}

void kc_bytes_set(kc_byte_array *list, size_t index, const void *val) {
    void* loc = _get(list, index);
    memcpy(loc, val, list->typeSize);
}

size_t kc_bytes_length(kc_byte_array* list) {
    return list->size;
}

size_t kc_bytes_capacity(kc_byte_array* list) {
    return list->capacity;
}

void kc_bytes_clear(kc_byte_array* list) {
    free(list->data);
    list->size = 0;
    list->data = malloc(list->typeSize * list->capacity);
    if(!list->data) {
        printf("Not enough memory!!\n");
        abort();
    }
}

int kc_bytes_isEmpty(kc_byte_array* list) {
    return list->size == 0 ? 1 : 0;
}

void kc_bytes_add(kc_byte_array* list, void* item) {
    if(list->size >= list->capacity)
    {
        increaseArraySize(list);
    }

    if (item) {
        memcpy(
            _get(list, list->size), 
            item, 
            list->typeSize
        );
    } else {
        memset(_get(list, list->size), 0, kc_bytes_getTypeSize(list));
    }

    list->size++;
}

void kc_bytes_insert(kc_byte_array* list, void* item, size_t index) {
    size_t dataSize = list->typeSize;

    if(list->size >= list->capacity) {
        increaseArraySize(list);
    }   

	size_t i;
    for(i = list->size; i > index; i--) {
        memcpy(_get(list, i), kc_bytes_get(list, i-1), dataSize);
    }

    memcpy(_get(list, index), item, dataSize);
    list->size++;
}

void kc_bytes_removeAt(kc_byte_array* list, size_t index) {
    size_t dataSize = list->typeSize;
	size_t i;
    for(i = index; i < list->size; i++) {
        memcpy(_get(list, i), kc_bytes_get(list, i+1), dataSize);
    }

    void* empty = alloca(dataSize);
    memcpy(_get(list, list->size-1), empty, dataSize);
    list->size--;
}

void kc_bytes_pop(kc_byte_array* list) {
    kc_bytes_removeAt(list, list->size - 1);
}

void kc_bytes_resize(kc_byte_array* list)
{
    void *newList = malloc(list->typeSize * list->capacity);
    if(!newList) {
        printf("Not enough memory!!\n");
        abort();
    }

    memcpy(newList, list->data, list->capacity * list->typeSize);

    free(list->data);
    list->data = newList;
}

