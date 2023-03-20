#ifndef _KGE_ENTITIES_H
#define _KGE_ENTITIES_H

#include <stdbool.h>
#include <stdarg.h>
#include "kc/set.h"
#include "Components.h"

// Check if component is present in archetype.
#define entity_archetype_has(arch, comp) _entity_archetype_has(arch, cp_type(comp))
// Create new archetype with these components.
#define entity_archetype_create(...) _entity_archetype_create(__VA_ARGS__, 0)

// Set wrapper for dealing with entity component combinations.
typedef struct entity_archetype {
	kc_set components;
} entity_archetype;

// Entity reference number.
typedef struct entity_entity {
	size_t index;
} entity_entity;

// Check if component is present in archetype.
bool _entity_archetype_has(entity_archetype arch, size_t comp);

// Create new archetype with these components.
entity_archetype _entity_archetype_create(COMPONENT_ENUM comp, ...);

// Deallocate memory used by archetype.
void entity_archetype_free(entity_archetype arch);

// Add a type to an archetype.
void entity_archetype_add_type(entity_archetype* arch, COMPONENT_ENUM cp);

// Remove a type from an archetype.
void entity_archetype_remove_type(entity_archetype* arch, COMPONENT_ENUM cp);

// Returns true if the two archetypes hold the same components.
bool entity_archetype_equals(entity_archetype a, entity_archetype b);

// Returns true if 'a' is a subset of 'b'.
bool entity_archetype_sub(entity_archetype a, entity_archetype b);

// Create a new archetype with the same contents as a.
entity_archetype entity_archetype_copy(entity_archetype a);

// Print archetype's component ids to stdout.
void print_entity_archetype(entity_archetype arch);
#endif // _KGE_ENTITIES_H
