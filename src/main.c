#include <stdio.h>
#include "EntityManager.h"
#include "kc/array.h"
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

	struct entity_manager* manager = entity_manager_create();
	entity_entity e1 = entity_manager_add_entity(manager, arch1);
	Transform tr = { .pos = { 0.1f, 0.2f, 54.f }, .size = { 2.f, 2.f }, .rotation = 90.f };
	entity_manager_set_component(manager, e1, cp_type(Transform), &tr);

	entity_entity e2 = entity_manager_add_entity(manager, arch2);
	Transform tr2 = { .pos = { 4.f, 231.43f, 54.f }, .size = { 5.f, 1.f }, .rotation = 0.321f };
	entity_manager_set_component(manager, e2, cp_type(Transform), &tr2);

	Transform tt;
	entity_manager_get_component(manager, e1, &tt, Transform);
	printf("Transform pos: %f, %f, %f, size: %f, %f, rot: %f\n", tt.pos.x, tt.pos.y, tt.pos.z, tt.size.x, tt.size.y, tt.rotation);
	entity_manager_get_component(manager, e2, &tt, Transform);
	printf("Transform pos: %f, %f, %f, size: %f, %f, rot: %f\n", tt.pos.x, tt.pos.y, tt.pos.z, tt.size.x, tt.size.y, tt.rotation);

	Sprite rsp;
	entity_manager_get_component(manager, e1, &rsp, Sprite);
	printf("Sprite id: %d, colour: %f, %f, %f, %f\n", rsp.id, rsp.color.x, rsp.color.y, rsp.color.z, rsp.color.w);
	entity_manager_get_component(manager, e2, &rsp, Sprite);
	printf("Sprite id: %d, colour: %f, %f, %f, %f\n", rsp.id, rsp.color.x, rsp.color.y, rsp.color.z, rsp.color.w);

	Sprite sp = { .id = 2, .color = { 0.1f, 0.2f, 0.3f, 0.4f }};
	entity_manager_set_component(manager, e1, cp_type(Sprite), &sp);

	Sprite sp2 = { .id = 5, .color = { 0.4f, 0.3f, 0.2f, 0.1f }};
	entity_manager_set_component(manager, e2, cp_type(Sprite), &sp2);

	entity_manager_get_component(manager, e1, &rsp, Sprite);
	printf("Sprite id: %d, colour: %f, %f, %f, %f\n", rsp.id, rsp.color.x, rsp.color.y, rsp.color.z, rsp.color.w);
	entity_manager_get_component(manager, e2, &rsp, Sprite);
	printf("Sprite id: %d, colour: %f, %f, %f, %f\n", rsp.id, rsp.color.x, rsp.color.y, rsp.color.z, rsp.color.w);

	entity_entity* all = entity_manager_all_entities(manager);
	printf("Entities: \n");
	for (size_t i = 0; i < kc_arr_len(all); i++)
		printf("%lu, ", all[i].index);
	printf("\n");
	kc_arr_free(all);

	entity_archetype aq = entity_archetype_create(cp_type(Sprite), cp_type(Transform));
	all = entity_manager_query_entities(manager, aq);
	printf("Entities query: \n");
	for (size_t i = 0; i < kc_arr_len(all); i++)
		printf("%lu, ", all[i].index);
	printf("\n");
	kc_arr_free(all);

	entity_archetype_free(arch1);
	entity_archetype_free(arch2);
	entity_archetype_free(aq);
	entity_manager_free(manager);
	manager = NULL;
}

