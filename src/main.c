#include <stddef.h>
#include <stdio.h>
#include "klm.h"
#include "kc/llist.h"
#include "kc/array.h"
#include "kc/set.h"

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

	printf("Start Hash test\n");
	int * int_set = NULL;
	kc_set_init(int_set, NULL);

	h = kc_arr_header(int_set);
	kc_set_item_pair(int_set);
	kc_set_set(int_set, (size_t)505);
	printf("Length: %lu, Capacity %lu, hash %p\n", h->length, h->capacity, (void*)h->hash);
	printf("Hash test %d\n", ((int)(h->hash(3513562354) % 16)));
	printf("Hash test %d\n", ((int)(h->hash(3513562355) % 16)));
	printf("Hash test %d\n", ((int)(h->hash(3513562356) % 16)));

	return 0;
}
