#ifndef _KGE_ENTITYMANAGER_H
#define _KGE_ENTITYMANAGER_H

#include "Components.h"
#include "Entities.h"
#include "kc/map.h"
#include "kc/byte_array.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

// Used by the entity_manager to store entities of like types.
struct _entity_store {
	entity_archetype type;
	kc_map entity_list;
	kc_byte_array** data;
};

// Store entity components for use.
struct entity_manager {
	struct kc_map entity_list;
	struct _entity_store* data_store;
};

// Create instance of entity_manager.
struct entity_manager* entity_manager_create();
// Deallocate entity_manager and all contained _entity_stores.
void entity_manager_free(struct entity_manager* manager);

// Return a kc_arr of all entities in the entity_manager.
entity_entity* entity_manager_all_entities(struct entity_manager* manager);
// Return a kc_arr of all entities in the entity_manager containing all components from arch.
entity_entity* entity_manager_query_entities(struct entity_manager* manager, entity_archetype arch);
// Create and return a new entity_entity of archetype arch.
entity_entity entity_manager_add_entity(struct entity_manager* manager, entity_archetype arch);
// Destory an entity_entity e.
void entity_manager_destroy(struct entity_manager* manager, entity_entity e);

// Get a pointer to the component's location in the entity manager.
const void* _entity_manager_get_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp);
// Get the component and copy it target location.
inline void _entity_manager_get_component_and_copy(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp, void* target) {
	assert(kc_map_has(manager->entity_list, entity.index));
	const void* c = _entity_manager_get_component(manager, entity, cp);
	memcpy(target, c, cp_size(cp));
}

// If a component is on an entity.
bool _entity_manager_has_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp);
// If a component is on an entity.
#define entity_manager_has_component(manager, entity, cp) _entity_manager_add_component(manager, entity, cp_type(cp))

// Add a component to an entity.
void _entity_manager_add_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp);
// Add a component to an entity.
#define entity_manager_add_component(manager, entity, cp) _entity_manager_add_component(manager, entity, cp_type(cp))
// Remove a component from an entity.
void _entity_manager_remove_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp);
// Remove a component from an entity.
#define entity_manager_remove_component(manager, entity, cp) _entity_manager_remove_component(manager, entity, cp_type(cp))

// Get a copy of the component.
#define entity_manager_get_component(manager, entity, t, cp) _entity_manager_get_component_and_copy(manager, entity, cp_type(cp), t)
// Get a const * to the component.
#define entity_manager_read_component(manager, entity, cp) (const cp*)_entity_manager_get_component(manager, entity, cp_type(cp)

// Update component.
void entity_manager_set_component(
		struct entity_manager* manager,
		entity_entity entity,
		COMPONENT_ENUM type,
		const void* component);

// create new entity store.
struct _entity_store _entity_store_create(entity_archetype arch);
// Deallocate entity store.
void _entity_store_free(struct _entity_store* store);

// Add an entity to the entity store.
void _entity_store_add_entity(
		struct _entity_store* store,
		entity_entity entity);
// Remove entity from entity store.
void _entity_store_remove_entity(
		struct _entity_store* store,
		entity_entity entity);

// Get a component from entity in the entity store.
const void* _entity_store_get_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM component);

// Update component in entity store.
void _entity_store_set_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM type,
		const void* component);

#endif // _KGE_ENTITYMANAGER_H
