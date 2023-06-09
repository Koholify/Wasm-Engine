#ifndef _KC_ARRAY_H
#define _KC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define kc_arr_header(t) ((((struct kc_array_header *) t) - 1))
#define kc_arr_len(t) (kc_arr_header(t)->length)
#define kc_arr_cap(t) (kc_arr_header(t)->capacity)

#define kc_arr_canadd(t, n) t = _kc_arr_canadd(t, n)

#define kc_arr_setcap(t, n) t = _kc_arr_setcap(t, n)
#define kc_arr_push(t, x) t = _kc_arr_push(t, x)
#define kc_arr_setlen(t, n) _kc_arr_setlen(t, n)
#define kc_arr_ins(t, i, x) (kc_arr_canadd(t, 1), memmove(t + (i + 1), t + i, sizeof(*t) * (kc_arr_len(t)++ - i)), t[i] = x)
#define kc_arr_pop(t) (t[kc_arr_header(t)->length--])
#define kc_arr_remove(t, i) (memmove(t + i, t + (i + 1), sizeof(*t) * (--(kc_arr_len(t)) - i)))

#define kc_arr_init(t) ((t) = kc_arr_setcap(t, 8))

struct kc_array_header {
	size_t capacity;
	size_t length;
};

void * kc_arr_grow(void * a, size_t size, size_t cap);
void kc_arr_free(void * a);

template<typename T> T _kc_arr_setcap(T array, size_t cap) {
	return (T) kc_arr_grow((void*)array, sizeof(*array), cap);
}


template<typename T> T* _kc_arr_push(T* t, T x) {
	t = kc_arr_canadd(t, 1);
	t[kc_arr_header(t)->length++] = x;
	return t;
}

template<typename T> void _kc_arr_setlen(T* t, size_t n) {
	if (t) {
		if (n > kc_arr_len(t)) {
			kc_arr_canadd(t, n - kc_arr_len(t));
		}
	} else {
		kc_arr_setcap(t, n);
	}

	kc_arr_header(t)->length = n;
}

template<typename T> T* _kc_arr_canadd(T* t, size_t n) {
	if (kc_arr_len(t) + ((int)n) > kc_arr_cap(t)) {
		return (T*)kc_arr_grow(t, sizeof(*t), kc_arr_len(t) + n);
	}
	return t;
}
#endif
