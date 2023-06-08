#include <stdio.h>

#include "Scene.h"
#include "InputSystem.h"
#include "Config.h"
#include "Entities.h"
#include "EntityManager.h"
#include "kc/map.h"
#include "kc/array.h"

#if KGE_TERMINAL
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

static entity_entity random_entity(struct entity_manager* manager) {
	entity_entity* all = entity_manager_all_entities(manager);
	srand(time(NULL));
	size_t ind = (size_t)rand() % kc_arr_len(all);
	entity_entity result = all[ind];
	kc_arr_free(all);
	return result;
}

void terminal_input_system(struct entity_manager* manager) {
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

#if KGE_WASM

void wasm_input_system(struct entity_manager* manager) {
	(void)manager;
}

#endif

