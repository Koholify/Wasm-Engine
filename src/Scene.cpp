#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "Components.h"
#include "Config.h"
#include "Scene.h"
#include "Entities.h"
#include "EntityManager.h"
#include "InputSystem.h"
#include "RenderingSystem.h"
#include "kc/array.h"
#include "klm.h"


kge_scene kge_scene_create(scene_update update) {
	kge_scene newScene = { };
	newScene.loop = update;
	newScene.manager = entity_manager_create();
	return newScene;
}

void kge_scene_update(kge_scene scene) {
	scene.loop(scene.manager);
}

void kge_scene_free(kge_scene scene) {
	entity_manager_free(scene.manager);
}

/**********************************************************************
 *
 * Systems
 *
 **********************************************************************/

static void velocity_system(struct entity_manager* manager) {
	entity_archetype arch = entity_archetype_create(cp_type(Velocity), cp_type(Transform));
	entity_entity* entities = entity_manager_query_entities(manager, arch);
	for (size_t i = 0; i < kc_arr_len(entities); i++) {
		entity_entity e = entities[i];
		Transform trans = { 0 };
		entity_manager_get_component(manager, e, &trans, Transform);
		Velocity vel = { 0 };
		entity_manager_get_component(manager, e, &vel, Velocity);

		if (trans.pos.x >= 0.5f || trans.pos.x <= -0.5f) vel.value.x *= -1.f;
		if (trans.pos.y >= 0.5f || trans.pos.y <= -0.5f) vel.value.y *= -1.f;
		vec3 v = { vel.value.x, vel.value.y, 0.f };
		trans.pos = klm_add_v3(trans.pos, v);
		entity_manager_set_component(manager, e, cp_type(Transform), &trans);
		entity_manager_set_component(manager, e, cp_type(Velocity), &vel);
	}
}

/**********************************************************************
 *
 * Play Scene
 *
 **********************************************************************/

static void scene_play_loop(struct entity_manager* manager) {
#if KGE_TERMINAL
	terminal_input_system(manager);
#endif
	velocity_system(manager);
	renderer_render_system(manager);
}

kge_scene kge_scene_play_create() {
	return kge_scene_create(scene_play_loop);
}
