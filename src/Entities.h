#ifndef _KGE_ENTITIES_H
#define _KGE_ENTITIES_H

#include <stdbool.h>
#include <stdarg.h>
#include "kc/set.h"
#include "Components.h"

#define entity_archetype_has(arch, comp) _entity_archetype_has(arch, cp_type(comp))
#define entity_archetype_create(...) _entity_archetype_create(__VA_ARGS__, 0)

typedef struct entity_archetype {
	kc_set components;
} entity_archetype;

typedef struct entity_entity {
	size_t index;
} entity_entity;

bool _entity_archetype_has(entity_archetype arch, size_t comp);
entity_archetype _entity_archetype_create(COMPONENT_ENUM comp, ...);
void entity_archetype_free(entity_archetype arch);
bool entity_archetype_equals(entity_archetype a, entity_archetype b);
bool entity_archetype_sub(entity_archetype a, entity_archetype b);
entity_archetype entity_archetype_copy(entity_archetype a);
void print_entity_archetype(entity_archetype arch);
#endif // _KGE_ENTITIES_H
