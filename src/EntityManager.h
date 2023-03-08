#ifndef _KGE_ENTITYMANAGER_H
#define _KGE_ENTITYMANAGER_H

#include "Components.h"
#include "Entities.h"
#include "kc/map.h"
#include "kc/byte_array.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

struct _entity_store {
	entity_archetype type;
	kc_map entity_list;
	kc_byte_array** data;
};

struct entity_manager {
	struct kc_map entity_list;
	struct _entity_store* data_store;
};

struct entity_manager* entity_manager_create();
void entity_manager_free(struct entity_manager* manager);

entity_entity* entity_manager_all_entities(struct entity_manager* manager);
entity_entity* entity_manager_query_entities(struct entity_manager* manager, entity_archetype arch);
entity_entity entity_manager_add_entity(struct entity_manager* manager, entity_archetype arch);
void entity_manager_destroy(struct entity_manager* manager, entity_entity e);

const void* _entity_manager_get_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp);
inline void _entity_manager_get_component_and_copy(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp, void* target) {
	assert(kc_map_has(manager->entity_list, entity.index));
	const void* c = _entity_manager_get_component(manager, entity, cp);
	memcpy(target, c, cp_size(cp));
}
#define entity_manager_get_component(manager, entity, t, cp) _entity_manager_get_component_and_copy(manager, entity, cp_type(cp), t)

void entity_manager_set_component(
		struct entity_manager* manager,
		entity_entity entity,
		COMPONENT_ENUM type,
		const void* component);

struct _entity_store _entity_store_create(entity_archetype arch);
void _entity_store_free(struct _entity_store* store);

void _entity_store_add_entity(
		struct _entity_store* store,
		entity_entity entity);
void _entity_store_remove_entity(
		struct _entity_store* store,
		entity_entity entity);

const void* _entity_store_get_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM component);

void _entity_store_set_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM type,
		const void* component);

#endif // _KGE_ENTITYMANAGER_H
