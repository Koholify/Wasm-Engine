#include <stddef.h>
#include <stdio.h>
#include "klm.h"
#include "kc/llist.h"
#include "kc/array.h"
#include "kc/set.h"

void print_ss(kc_strset s);

int main(void) {
	printf("Hello World!\n");

	klm_vec3 vec = { 1.0f, 23.0f, 5.0f };

	printf("vec y is %f\n", vec.y);
	
	kc_llist list = { 0 };
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

void print_ss(kc_strset s) {
	const char* str;
	kc_strset_iterator sit = kc_strset_iter(s);
	printf("[ ");
	while (kc_strset_next(&sit, &str)) {
		printf("%s, ", str);
	}
	printf("]\n");
}
