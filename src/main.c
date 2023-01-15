#include <stdio.h>
#include "klm.h"
#include "kc/llist.h"
#include "kc/array.h"

int main(void) {
	printf("Hello World!\n");

	klm_vec3 vec = { 1.0f, 23.0f, 5.0f };

	printf("vec y is %f\n", vec.y);
	
	kc_llist list = { };
	kc_llist_add_tail(&list, (void *) 5);
	kc_llist_add_tail(&list, (void *) 15);
	kc_llist_add_tail(&list, (void *) 25);

	kc_llist_node * c = list.head;
	while (c) {
		printf("%p %p\n", c->data, c->next);
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

	printf("%p set cap to 10\n", ints);
	kc_array_header * h = kc_arr_header(ints);
	printf("Length: %lu, Capacity %lu, Size: %lu\n", h->length, h->capacity, h->size);

	for (int i = 0; i < 16; i++) {
		klm_vec2 v = {i, i*i};
		kc_arr_push(ints, v);
	}

	printf("[");
	for (int i = 0; i < kc_arr_len(ints); i++) {
		printf(" (%f, %f) ", ints[i].x, ints[i].y);
	}
	printf("]\n");
	
	printf("Length: %lu, Capacity %lu, Size: %lu\n", h->length, h->capacity, h->size);
	kc_arr_free(ints);

	return 0;
}
