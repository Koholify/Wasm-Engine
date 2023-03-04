#include <stdio.h>
#include "EntityManager.h"
#include "tests.h"
#include "Components.h"
#include "Entities.h"

int main(void) {
	printf("Hello World!\n");
	//run_tests();

	entity_archetype arch1 = entity_archetype_create(cp_type(Transform), cp_type(Sprite));
	print_entity_archetype(arch1);

	entity_archetype arch2 = entity_archetype_create(cp_type(Transform), cp_type(Sprite), cp_type(Velocity));
	print_entity_archetype(arch2);
	
	printf("%d\n", entity_archetype_sub(arch2, arch1));

	entity_archetype_free(arch2);

	struct entity_manager* manager = entity_manager_create();
	entity_manager_add_entity(manager, arch1);
	entity_manager_free(manager);
	manager = NULL;
}

