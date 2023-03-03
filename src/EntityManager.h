#ifndef _KGE_ENTITYMANAGER_H
#define _KGE_ENTITYMANAGER_H

#include "Entities.h"
#include <stddef.h>
#include <stdint.h>

struct _entity_store {
	entity_archetype type;
	void** data;
};

struct entity_map {
	kc_set entity_list;
	void** store;
};

struct entity_manager {
	struct entity_map entity_list;
	struct _entity_store* data_store;
};

struct entity_manager* entity_manager_create();
void entity_manager_free(struct entity_manager* manager);

entity_entity entity_manager_add_entity(struct entity_manager* manager, entity_archetype arch);
void entity_manager_destroy(entity_entity e);

struct entity_map entity_map_create();
void entity_map_free(struct entity_map);

#endif // _KGE_ENTITYMANAGER_H
