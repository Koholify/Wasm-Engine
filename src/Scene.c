#include "Config.h"
#include "Scene.h"
#include "Entities.h"
#include "EntityManager.h"
#include "Components.h"
#include "kc/array.h"
#include "kc/map.h"
#include <stddef.h>
#include <stdio.h>

#if TARGET == TERMINAL
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#endif

kge_scene kge_scene_create(scene_update update) {
	kge_scene new = { 0 };
	new.loop = update;
	new.manager = entity_manager_create();
	return new;
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

static void dummy_system(struct entity_manager* manager) {
	(void)manager;
	printf("The dummy system is running\n");
}

#if TARGET == TERMINAL
static entity_entity random_entity(struct entity_manager* manager) {
	entity_entity* all = entity_manager_all_entities(manager);
	srand(time(NULL));
	size_t ind = (size_t)rand() % kc_arr_len(all);
	entity_entity result = all[ind];
	kc_arr_free(all);
	return result;
}

static void terminal_input_system(struct entity_manager* manager) {
	(void)manager;
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1) {
		if (iscntrl(c)) printf("%d\n", c);
		else printf("%d ('%c')\n", c, c);

		if (c == 'q') RUNNING = false;
		else if (c == 'a') {
			entity_archetype arch = entity_archetype_create(cp_type(Transform), cp_type(Velocity));
			entity_manager_add_entity(manager, arch);
			entity_archetype_free(arch);
			printf("Entity count: %lu\n", kc_map_len(manager->entity_list));
		} else if (c == 'd') {
			entity_entity* all = entity_manager_all_entities(manager);
			for(size_t i = 0; i < kc_arr_len(all); i++)
				entity_manager_destroy(manager, all[i]);
			kc_arr_free(all);
			printf("Entity count: %lu\n", kc_map_len(manager->entity_list));
		} else if ( c == 'c') {
			entity_entity re = random_entity(manager);
			COMPONENT_ENUM cp = (rand() % 3) + 1;
			_entity_manager_add_component(manager, re, cp);
		}
	}
}
#endif

/**********************************************************************
 *
 * Play Scene
 *
 **********************************************************************/

static void scene_play_loop(struct entity_manager* manager) {
#if TARGET == TERMINAL
	terminal_input_system(manager);
#endif
	dummy_system(manager);
	printf("finish a loop\n");
}

kge_scene kge_scene_play_create() {
	return kge_scene_create(scene_play_loop);
}
