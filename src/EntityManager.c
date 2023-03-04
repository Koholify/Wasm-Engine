#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "Components.h"
#include "Entities.h"
#include "EntityManager.h"
#include "kc/array.h"
#include "kc/map.h"
#include "kc/set.h"

struct entity_manager* entity_manager_create() {
	struct entity_manager* manager = malloc(sizeof(struct entity_manager));
	manager->entity_list = kc_map_init(32);
	manager->data_store = NULL;
	kc_arr_init(manager->data_store);
	return manager;
}

void entity_manager_free(struct entity_manager *manager) {
	kc_arr_free(manager->data_store);
}

static size_t get_next_entity_id() {
	static size_t id = 1;
	return id++;
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
		struct _entity_store new_store = _entity_store_create(arch);
		kc_arr_push(manager->data_store, new_store);
		store = manager->data_store + kc_arr_len(manager->data_store);
	}

	struct entity_entity entity = { .index = get_next_entity_id() };
	_entity_store_add_entity(store, entity);
	kc_map_set(&manager->entity_list, entity.index, (void*)store);
	return entity;
}

void entity_manager_destroy(entity_entity e);


/********************************************************************
 *
 * Entity Store
 *
 ********************************************************************
 ********************************************************************/

struct _entity_store _entity_store_create(entity_archetype arch) {
	struct _entity_store new;
	new.type = entity_archetype_copy(arch);
	new.entity_list = kc_set_init(16);
	new.data = NULL;
	size_t len = kc_set_len(arch.components);
	kc_arr_setlen(new.data, len);
	
	size_t val;
	kc_set_iterator it = kc_set_iter(arch.components);
	
	for (size_t i = 0; i < kc_arr_len(new.data); i++) {
		kc_set_next(&it, &val);
		kc_arr_setlen(new.data[i], 16 * cp_size((COMPONENT_ENUM)val));
	}
	return new;
}

void _entity_store_add_entity(struct _entity_store* store, entity_entity entity) {
	size_t oldCap = kc_set_cap(store->entity_list);
	kc_set tempSet = {.data = NULL };

	if (kc_set_len(store->entity_list) > oldCap * 0.75f) {
		tempSet = kc_set_copy(store->entity_list);
	}

	kc_set_set(&store->entity_list, entity.index);
	size_t newCap = kc_set_cap(store->entity_list);

	if (tempSet.data) {
		size_t val;
		kc_set_iterator it = kc_set_iter(store->type.components);
		for (size_t i = 0; i < kc_arr_len(store->data); i++) {
			kc_set_next(&it, &val);
			size_t valSize = cp_size(val);
			kc_arr_setlen(store->data[i], newCap * valSize);

			char* temp = NULL;
			kc_set_iterator it2 = kc_set_iter(tempSet);
			kc_arr_setlen(temp, newCap * valSize);
			while (kc_set_next(&it2, &val)) {
				size_t indOld = kc_set_getIndex(tempSet, val);
				size_t indNew = kc_set_getIndex(store->entity_list, val);
				memcpy(temp + (indNew * valSize), store->data[i] + (indOld * valSize), valSize);
			}

			memcpy(store->data[i], temp, kc_arr_cap(temp));
			kc_arr_free(temp);
		}
		kc_set_free(tempSet);
	}
}

void _entity_store_free(struct _entity_store *store) {
	entity_archetype_free(store->type);
	for (size_t i = 0; i < kc_arr_len(store->data); i++)
		kc_arr_free(store->data[i]);
	kc_arr_free(store->data);
}

void* _entity_store_get_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM component) {
	if (!kc_set_has(store->type.components, component)) return NULL;
	kc_set_iterator it = kc_set_iter(store->type.components);
	size_t val = 0, i = 0;
	while (kc_set_next(&it, &val)) {
		if (val == component) break;
		i++;
	}

	size_t index = kc_set_getIndex(store->entity_list, entity.index);
	return store->data[i] + (index * cp_size(component));
}

