#include <assert.h>
#include <exception>
#include <map>
#include <vector>
#include <strstream>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "Components.h"
#include "Entities.h"
#include "EntityManager.h"
#include "RenderingSystem.h"
#include "cheerp/clientlib.h"
#include "kc/array.h"
#include "kc/byte_array.h"
#include "kc/map.h"
#include "kc/set.h"

[[cheerp::genericjs]] static void senderror(int i) {
	std::strstream ss;
	ss << "error " << i;
	client::console.log(ss.str());
}
struct entity_manager* entity_manager_create() {
	struct entity_manager* manager = (struct entity_manager*)malloc(sizeof(struct entity_manager));
	manager->entity_list = kc_map_init(32);
	manager->data_store = std::vector<_entity_store*>();
	manager->data_store.reserve(8);
	return manager;
}

void entity_manager_free(struct entity_manager *manager) {
	for(auto store : manager->data_store) {
		_entity_store_free(store);
	}
	kc_map_free(manager->entity_list);
}

static size_t get_next_entity_id() {
	static size_t id = 1;
	return id++;
}

static struct _entity_store* entity_manager_create_store(struct entity_manager* manager, entity_archetype arch) {
		struct _entity_store* new_store = _entity_store_create(arch);
		manager->data_store.push_back(new_store);
		return manager->data_store[manager->data_store.size() - 1];
}	

static struct _entity_store* entity_manager_find_store(struct entity_manager* manager, entity_archetype arch) {
	struct _entity_store* store = NULL;
	for (size_t i = 0; i < manager->data_store.size(); i++) {
		if (entity_archetype_equals(manager->data_store[i]->type, arch)) {
			store = manager->data_store [i];
			break;
		}
	}

	return store;
}

static struct _entity_store* get_or_create_store(struct entity_manager* manager, entity_archetype arch) {
	struct _entity_store* store = entity_manager_find_store(manager, arch);
	if (!store) {
		senderror(104);
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
	all = kc_arr_setcap(all, kc_map_len(manager->entity_list) + 1);
	kc_map_foreach(manager->entity_list, &all, all_job1);
	return  all;
}

entity_entity* entity_manager_query_entities(struct entity_manager* manager, entity_archetype arch) {
	entity_entity* all = NULL;
	kc_arr_setcap(all, 1);
	for(size_t i = 0; i < manager->data_store.size(); i++) {
		if (entity_archetype_sub(arch, manager->data_store[i]->type)) {
			struct _entity_store* store = manager->data_store[i];
			kc_arr_setcap(all, kc_arr_cap(all) + kc_map_len(store->entity_list));
			kc_map_foreach(store->entity_list, &all, all_job1);
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
	for (auto val : arch.components) {
		COMPONENT_ENUM ce = (COMPONENT_ENUM)val;
		const void* cp = _entity_store_get_component(b, entity, ce);
		_entity_store_set_component(a, entity, ce, cp);
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

struct _entity_store* _entity_store_create(entity_archetype arch) {
	struct _entity_store* newStore = new _entity_store;
	newStore->type = entity_archetype_copy(arch);
	newStore->entity_list = kc_map_init(16);
	newStore->data = std::map<COMPONENT_ENUM, kc_byte_array*>();
	
	senderror(5);
	for(auto val : arch.components) {
		kc_byte_array* ba = kc_bytes_create(16, cp_size((COMPONENT_ENUM)val));
		newStore->data[val] = ba;
	}

	for (auto kv : newStore->data) {
		senderror(kv.first);
		senderror((int)kv.second);
	}

	return newStore;
}

void _entity_store_add_entity(struct _entity_store* store, entity_entity entity) {
	size_t ind = kc_map_len(store->entity_list);
	kc_map_set(&store->entity_list, entity.index, (void*)ind);

	senderror(store->data.size());
	for(auto it : store->data) {
		kc_bytes_add(store->data[it.first], NULL);
		senderror((int)it.first);
		senderror((int)it.second);
	}
}

static void remove_store_lambda(kc_map_item* item, void* ind) {
	size_t i = (size_t)ind;
	item->value = (size_t)item->value >= i ? (void*)((size_t)item->value - 1) : item->value;
}

void _entity_store_remove_entity(struct _entity_store* store, entity_entity entity) {
	void* ind = kc_map_get(store->entity_list, entity.index);
	kc_map_foreach(store->entity_list, ind, remove_store_lambda);

	for (auto kv : store->data) {
		kc_bytes_removeAt(kv.second, (size_t)ind);
	}
	kc_map_remove(store->entity_list, entity.index);
}

void _entity_store_free(struct _entity_store *store) {
	entity_archetype_free(store->type);
	kc_map_free(store->entity_list);
	for( auto& kv : store->data)
		kc_bytes_free(kv.second);
	delete store;
}

static struct kc_byte_array* _store_get_array(struct _entity_store* store, COMPONENT_ENUM component) {
	return store->data[component];
}

const void* _entity_store_get_component(
		struct _entity_store* store,
		entity_entity entity,
		COMPONENT_ENUM component) {
	if (store->type.components.find(component) == store->type.components.end()) return NULL;
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

