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

	int * ints;
	kc_arr_init(ints);

	for (int i = 0; i < 5; i++) {
		kc_arr_push(ints, i * i);
	}

	printf("[");
	for (int i = 0; i < kc_arr_len(ints); i++) {
		printf(" %d ", ints[i]);
	}
	printf("]\n");

	return 0;
}
