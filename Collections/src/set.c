#include <stddef.h>
#include "kc/set.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

size_t kc_set_defaultHash(size_t in) {
	size_t hash = FNV_OFFSET;
	hash = hash ^ in;
	hash = hash * FNV_PRIME;
	return hash;
}
