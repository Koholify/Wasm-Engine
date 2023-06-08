#include <stddef.h>
#include <stdio.h>

#include "Config.h"
#include "Scene.h"
#include "Entities.h"
#include "EntityManager.h"
#include "InputSystem.h"
#include "RenderingSystem.h"


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

/**********************************************************************
 *
 * Play Scene
 *
 **********************************************************************/

static void scene_play_loop(struct entity_manager* manager) {
#if KGE_TERMINAL
	terminal_input_system(manager);
#endif
	renderer_render_system(manager);
}

kge_scene kge_scene_play_create() {
	return kge_scene_create(scene_play_loop);
}
