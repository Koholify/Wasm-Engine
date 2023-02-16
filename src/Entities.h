#ifndef _KGE_ENTITIES_H
#define _KGE_ENTITIES_H

#include "kc/set.h"
#include <stdbool.h>
#include <stdarg.h>

#define cp_type(comp) ((size_t)GET_COMPONENT_VALUE_##comp)
#define entity_archetype_has(arch, comp) _entity_archetype_has(arch, cp_type(comp)

typedef struct entity_archetype {
	kc_set components;
} entity_archetype;

bool _entity_archetype_has(entity_archetype arch, size_t comp);
entity_archetype entity_archetype_create(size_t comp, ...);
#endif // _KGE_ENTITIES_H
