#ifndef _KC_SET_H
#define _KC_SET_H

#include <stddef.h>
#include <stdbool.h>
#include "kc/array.h"

#define kc_set_len(t) (kc_arr_len(t))
#define kc_set_cap(t) (kc_arr_cap(t))
#define kc_set_hash(t) (kc_arr_header(t)->hash)
#define kc_set_is_used(t) (kc_arr_header(t)->is_used)
#define _kc_set_get_hash(t, v) (kc_set_hash(t)(v) % kc_arr_cap(t))
#define kc_set_has(t, v) (kc_set_is_used(t)[_kc_set_get_hash(t, v)])
#define kc_set_set(t, v) size_t hashed = _kc_set_get_hash(t, v);(t[hashed] = v);(kc_set_is_used(t)[hashed]?0:kc_arr_len(t)++);kc_set_is_used(t)[hashed] = true;

#define kc_set_init(t, h) ((t) = kc_arr_grow((void*)t, sizeof(*t) + sizeof(bool), 16), \
																(kc_set_hash(t) = h ? h : kc_set_defaultHash), \
																(kc_set_is_used(t) = (bool*)(t + kc_arr_cap(t))), \
																(memset(kc_set_is_used(t), 0, sizeof(bool) * 16)))

size_t kc_set_defaultHash(size_t in);

#endif
