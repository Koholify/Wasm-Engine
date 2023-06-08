#include <stddef.h>
#include <stdio.h>
#include "tests.h"
#include "klm.h"
#include "kc/llist.h"
#include "kc/array.h"
#include "kc/set.h"
#include "Entities.h"
#include "EntityManager.h"

static void print_ss(kc_strset s);

static int llist_test() {
	klm_vec3 vec = { 1.0f, 23.0f, 5.0f };

	printf("vec y is %f\n", vec.y);
	
	kc_llist list = { };
	kc_llist_add_tail(&list, (void *) 5);
	kc_llist_add_tail(&list, (void *) 15);
	kc_llist_add_tail(&list, (void *) 25);

	kc_llist_node * c = list.head;
	while (c) {
		printf("%p %p\n", c->data, (void*)c->next);
		c = c->next;
	}
	printf("loop end \n");

	while(list.head) {
		size_t d = (unsigned long)kc_llist_remove_tail(&list);
		printf("%lu ", d);
	}
	printf("\nLinked List Complete\n");
	return 0;
}

static int arr_test() {
	klm_vec2 * ints = NULL;
	// kc_arr_init(ints);
	kc_arr_setcap(ints, 10);

	printf("%p set cap to 10\n", (void*)ints);
	struct kc_array_header * h = kc_arr_header(ints);
	printf("Length: %lu, Capacity %lu\n", h->length, h->capacity);

	for (int i = 0; i < 8; i++) {
		klm_vec2 v = {i, i*i};
		kc_arr_push(ints, v);
	}

	printf("[");
	for (size_t i = 0; i < kc_arr_len(ints); i++) {
		printf(" (%.2f, %.2f) ", ints[i].x, ints[i].y);
	}
	printf("]\n");
	
	klm_vec2 v = { 4.5f, 12.52f };
	klm_vec2 v2 = { 3.1f, 54.67f };
	klm_vec2 v3 = { 4.1f, 18.67f };
	kc_arr_ins(ints, 3, v);
	kc_arr_ins(ints, 0, v2);
	kc_arr_ins(ints, 8, v3);

	printf("[");
	for (size_t i = 0; i < kc_arr_len(ints); i++) {
		printf(" (%.2f, %.2f) ", ints[i].x, ints[i].y);
	}
	printf("]\n");

	v = kc_arr_pop(ints);
	v = kc_arr_pop(ints);
	kc_arr_remove(ints, 7);
	kc_arr_remove(ints, 2);

	printf("[");
	for (size_t i = 0; i < kc_arr_len(ints); i++) {
		printf(" (%.2f, %.2f) ", ints[i].x, ints[i].y);
	}
	printf("]\n");
	
	h = kc_arr_header(ints);
	printf("Length: %lu, Capacity %lu\n", h->length, h->capacity);
	kc_arr_free(ints);
	return 0;
}

static int set_test() {
	kc_set set = kc_set_init(8);
	kc_set_set(&set, 543);
	kc_set_set(&set, 231);
	kc_set_set(&set, 641);
	kc_set_set(&set, 79);

	kc_set set2 = kc_set_init(16);
	kc_set_set(&set2, 5111);
	kc_set_set(&set2, 641);
	kc_set_set(&set2, 45952);
	kc_set_set(&set2, 48782);
	kc_set_set(&set2, 231);
	
	kc_set set3 = kc_set_intersect(set, set2);
	kc_set set4 = kc_set_union(set, set2);
	kc_set set5 = kc_set_difference(set, set2);

	kc_set_iterator it = kc_set_iter(set3);
	size_t val;
	while(kc_set_next(&it, &val)) {
		printf("%lu, ", val);
	}
	printf("\n");

	it = kc_set_iter(set4);
	while(kc_set_next(&it, &val)) {
		printf("%lu, ", val);
	}
	printf("\n");

	it = kc_set_iter(set5);
	while(kc_set_next(&it, &val)) {
		printf("%lu, ", val);
	}
	
	printf("\n");
	kc_set_free(set);
	kc_set_free(set2);
	kc_set_free(set3);
	kc_set_free(set4);
	kc_set_free(set5);

	kc_strset ss = kc_strset_init(16);
	kc_strset ss2 = kc_strset_init(16);

	kc_strset_set(&ss, "Hello");
	kc_strset_set(&ss, "World");
	kc_strset_set(&ss, "Set");
	kc_strset_set(&ss, "One");

	kc_strset_set(&ss2, "Two");
	kc_strset_set(&ss2, "Sets");
	kc_strset_set(&ss2, "Wowo");
	kc_strset_set(&ss2, "Hello");
	kc_strset_set(&ss2, "Goodbye");
	kc_strset_set(&ss2, "One");

	print_ss(ss);
	printf("index of Hello %d\n", kc_strset_getIndex(ss, "Hello"));

	printf("\nset 2\n");
	print_ss(ss2);

	kc_strset ss3 = kc_strset_union(ss, ss2);
	kc_strset ss4 = kc_strset_intersect(ss, ss2);
	kc_strset ss5 = kc_strset_difference(ss, ss2);

	printf("\nunion\n");
	print_ss(ss3);
	printf("\nintersect\n");
	print_ss(ss4);
	printf("\ndiff\n");
	print_ss(ss5);

	return 0;
}

static int entity_test() {
	entity_archetype arch1 = entity_archetype_create(cp_type(Transform), cp_type(Sprite));
	print_entity_archetype(arch1);

	entity_archetype arch2 = entity_archetype_create(cp_type(Transform), cp_type(Sprite), cp_type(Velocity));
	print_entity_archetype(arch2);
	
	printf("%d\n", entity_archetype_sub(arch2, arch1));

	struct entity_manager* manager = entity_manager_create();
	entity_entity e1 = entity_manager_add_entity(manager, arch1);
	Transform tr = { { 0.1f, 0.2f, 54.f }, { 2.f, 2.f }, 90.f };
	entity_manager_set_component(manager, e1, cp_type(Transform), &tr);

	entity_entity e2 = entity_manager_add_entity(manager, arch2);
	Transform tr2 = { { 4.f, 231.43f, 54.f }, { 5.f, 1.f }, 0.321f };
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

	Sprite sp = { 2, { 0.1f, 0.2f, 0.3f, 0.4f }};
	entity_manager_set_component(manager, e1, cp_type(Sprite), &sp);

	Sprite sp2 = { 5, { 0.4f, 0.3f, 0.2f, 0.1f }};
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
	return 0;
}

static void print_ss(kc_strset s) {
	const char* str;
	kc_strset_iterator sit = kc_strset_iter(s);
	printf("[ ");
	while (kc_strset_next(&sit, &str)) {
		printf("%s, ", str);
	}
	printf("]\n");
}

void run_tests() {
	printf("Hello World!\n");
	llist_test();
	arr_test();
	set_test();
	entity_test();
}
