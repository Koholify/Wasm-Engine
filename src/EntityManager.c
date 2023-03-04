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
	kc_map_free(manager->entity_list);
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
		store = manager->data_store + (kc_arr_len(manager->data_store) - 1);
	}

	struct entity_entity entity = { .index = get_next_entity_id() };
	_entity_store_add_entity(store, entity);
	kc_map_set(&manager->entity_list, entity.index, (void*)store);
	return entity;
}

void entity_manager_destroy(struct entity_manager* manager, entity_entity e) {
	struct _entity_store* store = kc_map_get(manager->entity_list, e.index);
	_entity_store_remove_entity(store, e);
	kc_map_remove(manager->entity_list, e.index);
}

/********************************************************************
 *
 * Entity Store
 *
 ********************************************************************
 ********************************************************************/

struct _entity_store _entity_store_create(entity_archetype arch) {
	struct _entity_store new;
	new.type = entity_archetype_copy(arch);
	new.entity_list = kc_map_init(16);
	new.data = NULL;
	size_t len = kc_set_len(arch.components);
	kc_arr_setlen(new.data, len);
	
	size_t val;
	kc_set_iterator it = kc_set_iter(arch.components);
	
	for (size_t i = 0; i < kc_arr_len(new.data); i++) {
		kc_set_next(&it, &val);
		kc_arr_setcap(new.data[i], 16 * cp_size(val));
	}
	return new;
}

void _entity_store_add_entity(struct _entity_store* store, entity_entity entity) {
	size_t ind = kc_map_len(store->entity_list);
	kc_map_set(&store->entity_list, entity.index, (void*)ind);

	size_t val;
	kc_set_iterator it = kc_set_iter(store->type.components);
	
	for (size_t i = 0; i < kc_arr_len(store->data); i++) {
		kc_set_next(&it, &val);
		size_t ol = kc_arr_len(store->data[i]);
		kc_arr_setlen(store->data[i], ol + cp_size(val));
		memset(&(store->data[i][ind]), 0, cp_size(val));
	}
}

static void remove_store_lambda(kc_map_item* item, void* ind) {
	size_t i = (size_t)ind;
	item->value = (size_t)item->value >= i ? (void*)((size_t)item->value - 1) : item->value;
}

void _entity_store_remove_entity(struct _entity_store* store, entity_entity entity) {
	void* ind = kc_map_get(store->entity_list, entity.index);
	kc_map_foreach(store->entity_list, ind, remove_store_lambda);

	size_t val;
	kc_set_iterator it = kc_set_iter(store->type.components);
	
	for (size_t i = 0; i < kc_arr_len(store->data); i++) {
		kc_set_next(&it, &val);
		size_t size = cp_size(val);
		size_t index = (size_t)ind * size;
		memmove(&(store->data[i][index]), &(store->data[i][index + size]), (kc_arr_len(store->data[i]) - index));
		struct kc_array_header* h = kc_arr_header(store->data[i]);
		h->length = h->length - size;
	}
}

void _entity_store_free(struct _entity_store *store) {
	entity_archetype_free(store->type);
	kc_map_free(store->entity_list);
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

	size_t index = (size_t)kc_map_get(store->entity_list, entity.index);
	return store->data[i] + (index * cp_size(component));
}

