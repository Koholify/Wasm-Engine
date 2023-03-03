#include <stdlib.h>
#include "Entities.h"
#include "EntityManager.h"
#include "kc/array.h"
#include "kc/set.h"

struct entity_manager* entity_manager_create() {
	struct entity_manager* manager = malloc(sizeof(struct entity_manager));
	manager->entity_list = entity_map_create();
	manager->data_store = NULL;
	kc_arr_init(manager->data_store);
	return manager;
}

void entity_manager_free(struct entity_manager *manager) {
	kc_arr_free(manager->data_store);
}

entity_entity entity_manager_add_entity(struct entity_manager* manager, entity_archetype arch) {
	struct _entity_store* store = NULL;
	for (size_t i = 0; i < kc_arr_len(manager->data_store); i++) {
		if (entity_archetype_equals(manager->data_store[i].type, arch)) {
			store = manager->data_store + i;
			break;
		}
	}

	if (!store) {

		kc_arr_push(manager->data_store, );
}

void entity_manager_destroy(entity_entity e);

/********************************************************************
 *
 * Entity Map
 *
 ********************************************************************
 ********************************************************************/

struct entity_map entity_map_create() {
	struct entity_map new;
	new.entity_list = kc_set_init(32);
	new.store = NULL;
	kc_arr_setcap(new.store, 32);
	return new;
}

void entity_map_free(struct entity_map map) {
	kc_arr_free(map.store);
	kc_set_free(map.entity_list);
}
