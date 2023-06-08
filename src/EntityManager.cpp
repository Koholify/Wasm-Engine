#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "Components.h"
#include "Entities.h"
#include "EntityManager.h"
#include "kc/array.h"
#include "kc/byte_array.h"
#include "kc/map.h"
#include "kc/set.h"

struct entity_manager* entity_manager_create() {
	struct entity_manager* manager = (struct entity_manager*)malloc(sizeof(struct entity_manager));
	manager->entity_list = kc_map_init(32);
	manager->data_store = NULL;
	kc_arr_setcap(manager->data_store, 8);
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

static struct _entity_store* entity_manager_create_store(struct entity_manager* manager, entity_archetype arch) {
		struct _entity_store new_store = _entity_store_create(arch);
		kc_arr_push(manager->data_store, new_store);
		return manager->data_store + (kc_arr_len(manager->data_store) - 1);
}	

static struct _entity_store* entity_manager_find_store(struct entity_manager* manager, entity_archetype arch) {
	struct _entity_store* store = NULL;
	for (size_t i = 0; i < kc_arr_len(manager->data_store); i++) {
		if (entity_archetype_equals(manager->data_store[i].type, arch)) {
			store = manager->data_store + i;
			break;
		}
	}

	return store;
}

static struct _entity_store* get_or_create_store(struct entity_manager* manager, entity_archetype arch) {
	struct _entity_store* store = entity_manager_find_store(manager, arch);
	if (!store) {
		store = entity_manager_create_store(manager, arch);
	}
	return store;
}

entity_entity entity_manager_add_entity(struct entity_manager* manager, entity_archetype arch) {
	struct _entity_store* store = get_or_create_store(manager, arch);
	struct entity_entity entity = { get_next_entity_id() };
	_entity_store_add_entity(store, entity);
	kc_map_set(&manager->entity_list, entity.index, (void*)store);
	return entity;
}

void entity_manager_destroy(struct entity_manager* manager, entity_entity e) {
	struct _entity_store* store = (struct _entity_store*)kc_map_get(manager->entity_list, e.index);
	_entity_store_remove_entity(store, e);
	kc_map_remove(manager->entity_list, e.index);
}

static void all_job1(kc_map_item* i, void* l) {
	entity_entity** r = (entity_entity**)l;
	entity_entity* all = *r;
	entity_entity v = { (size_t)(i->key) };
	kc_arr_push(all, v);
	*r = all;
}
entity_entity* entity_manager_all_entities(struct entity_manager* manager) {
	entity_entity* all = NULL;
	kc_arr_setcap(all, kc_map_len(manager->entity_list) + 1);
	kc_map_foreach(manager->entity_list, &all, all_job1);
	return  all;
}

entity_entity* entity_manager_query_entities(struct entity_manager* manager, entity_archetype arch) {
	entity_entity* all = NULL;
	kc_arr_setcap(all, 1);
	for(size_t i = 0; i < kc_arr_len(manager->data_store); i++) {
		if (entity_archetype_sub(arch, manager->data_store[i].type)) {
			struct _entity_store store = manager->data_store[i];
			kc_arr_setcap(all, kc_arr_cap(all) + kc_map_len(store.entity_list));
			kc_map_foreach(store.entity_list, &all, all_job1);
		}
	}
	return  all;
}

extern inline void _entity_manager_get_component_and_copy(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp, void* target); 

const void* _entity_manager_get_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp) {
	struct _entity_store* store = (struct _entity_store*)kc_map_get(manager->entity_list, entity.index);
	return _entity_store_get_component(store, entity, cp);
}

void entity_manager_set_component(
		struct entity_manager* manager,
		entity_entity entity,
		COMPONENT_ENUM type,
		const void* component) {
	struct _entity_store* store = (struct _entity_store*)kc_map_get(manager->entity_list, entity.index);
	_entity_store_set_component(store, entity, type, component);
}

bool _entity_manager_has_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp) {
	assert(kc_map_has(manager->entity_list, entity.index));
	struct _entity_store* store = (struct _entity_store*)kc_map_get(manager->entity_list, entity.index);
	return _entity_archetype_has(store->type, cp);
}

static void copy_entity_data(struct _entity_store* a, struct _entity_store* b, entity_entity entity, entity_archetype arch) {
	kc_set_iterator it = kc_set_iter(arch.components);
	size_t val;
	while(kc_set_next(&it, &val)) {
		const void* cp = _entity_store_get_component(b, entity, val);
		_entity_store_set_component(a, entity, val, cp);
	}
}
void _entity_manager_add_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp) {
	if (_entity_manager_has_component(manager, entity, cp))
			return;

	struct _entity_store* current_store = (struct _entity_store*)kc_map_get(manager->entity_list, entity.index);
	entity_archetype arch = entity_archetype_copy(current_store->type);
	entity_archetype_add_type(&arch, cp);

	struct _entity_store* new_store = get_or_create_store(manager, arch);
	_entity_store_add_entity(new_store, entity);
	copy_entity_data(new_store, current_store, entity, current_store->type);
	_entity_store_remove_entity(current_store, entity);
	kc_map_set(&manager->entity_list, entity.index, new_store);
	entity_archetype_free(arch);
}

void _entity_manager_remove_component(struct entity_manager* manager, entity_entity entity, COMPONENT_ENUM cp) {
	if (!_entity_manager_has_component(manager, entity, cp))
			return;

	struct _entity_store* current_store = (struct _entity_store*)kc_map_get(manager->entity_list, entity.index);
	entity_archetype arch = entity_archetype_copy(current_store->type);
	entity_archetype_remove_type(&arch, cp);

	struct _entity_store* new_store = get_or_create_store(manager, arch);
	_entity_store_add_entity(new_store, entity);
	copy_entity_data(new_store, current_store, entity, current_store->type);
	_entity_store_remove_entity(current_store, entity);
	kc_map_set(&manager->entity_list, entity.index, new_store);
	entity_archetype_free(arch);
}

/********************************************************************
 *
 * Entity Store
 *
 ********************************************************************
 ********************************************************************/

struct _entity_store _entity_store_create(entity_archetype arch) {
	struct _entity_store newStore;
	newStore.type = entity_archetype_copy(arch);
	newStore.entity_list = kc_map_init(16);
	newStore.data = NULL;
	size_t len = kc_set_len(arch.components);
	kc_arr_setlen(newStore.data, len);
	
	size_t val;
	kc_set_iterator it = kc_set_iter(arch.components);
	
	for (size_t i = 0; i < kc_arr_len(newStore.data); i++) {
		kc_set_next(&it, &val);
		newStore.data[i] = kc_bytes_create(16, cp_size(val));
	}
	return newStore;
}

void _entity_store_add_entity(struct _entity_store* store, entity_entity entity) {
	size_t ind = kc_map_len(store->entity_list);
	kc_map_set(&store->entity_list, entity.index, (void*)ind);

	for (size_t i = 0; i < kc_arr_len(store->data); i++) {
		kc_bytes_add(store->data[i], NULL);
	}
}

static void remove_store_lambda(kc_map_item* item, void* ind) {
	size_t i = (size_t)ind;
	item->value = (size_t)item->value >= i ? (void*)((size_t)item->value - 1) : item->value;
}

void _entity_store_remove_entity(struct _entity_store* store, entity_entity entity) {
	void* ind = kc_map_get(store->entity_list, entity.index);
	kc_map_foreach(store->entity_list, ind, remove_store_lambda);

	for (size_t i = 0; i < kc_arr_len(store->data); i++) {
		kc_bytes_removeAt(store->data[i], (size_t)ind);
	}
	kc_map_remove(store->entity_list, entity.index);
}

void _entity_store_free(struct _entity_store *store) {
	entity_archetype_free(store->type);
	kc_map_free(store->entity_list);
	for (size_t i = 0; i < kc_arr_len(store->data); i++)
		kc_bytes_free(store->data[i]);
	kc_arr_free(store->data);
}

static struct kc_byte_array* _store_get_array(struct _entity_store* store, COMPONENT_ENUM component) {
	kc_set_iterator it = kc_set_iter(store->type.components);
	size_t val = 0, i = 0;
	while (kc_set_next(&it, &val)) {
		if (val == component) break;
		i++;
	}
	return store->data[i];
}

const void* _entity_store_get_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM component) {
	if (!kc_set_has(store->type.components, component)) return NULL;
	kc_byte_array* data = _store_get_array(store, component);

	size_t index = (size_t)kc_map_get(store->entity_list, entity.index);
	return kc_bytes_get(data, index);
}

void _entity_store_set_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM type,
		const void* component) {
	kc_byte_array* data = _store_get_array(store, type);
	size_t index = (size_t)kc_map_get(store->entity_list, entity.index);
	kc_bytes_set(data, index, component);
}

