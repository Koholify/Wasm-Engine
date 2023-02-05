#ifndef _KC_SET_H
#define _KC_SET_H

#include <stddef.h>
#include <stdbool.h>
#include "kc/array.h"

#define kc_set_hash(t) (kc_arr_header(t)->hash)
#define kc_set_item_pair(t) struct { bool used; (*t) data; };
#define kc_set_init(t, h) ((t) = kc_arr_grow((void*)t, sizeof(*t) + sizeof(bool), 16), (kc_set_hash(t) = h ? h : kc_set_defaultHash))
#define _kc_set_get(t, v) ((kc_set_item_pair(t)*)t[kc_set_hash(v) % kc_arr_cap(t)])
#define kc_set_set(t, v) (_kc_set_get(t, v).data = v, \
													!_kc_set_get(t, v).used ? kc_arr_len(t)++ : 0)

size_t kc_set_defaultHash(size_t in);

#endif
