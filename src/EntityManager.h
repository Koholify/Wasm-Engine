#ifndef _KGE_ENTITYMANAGER_H
#define _KGE_ENTITYMANAGER_H

#include "Components.h"
#include "Entities.h"
#include "kc/map.h"
#include <stddef.h>
#include <stdint.h>

struct _entity_store {
	entity_archetype type;
	kc_map entity_list;
	char** data;
};

struct entity_manager {
	struct kc_map entity_list;
	struct _entity_store* data_store;
};

struct entity_manager* entity_manager_create();
void entity_manager_free(struct entity_manager* manager);

entity_entity entity_manager_add_entity(struct entity_manager* manager, entity_archetype arch);
void entity_manager_destroy(struct entity_manager* manager, entity_entity e);

struct _entity_store _entity_store_create(entity_archetype arch);
void _entity_store_free(struct _entity_store* store);

void _entity_store_add_entity(
		struct _entity_store* store,
		entity_entity entity);
void _entity_store_remove_entity(
		struct _entity_store* store,
		entity_entity entity);

void* _entity_store_get_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM component);

#endif // _KGE_ENTITYMANAGER_H
