#ifndef _KC_LLIST_H_
#define _KC_LLIST_H_

// Doubley Linked List Node.
typedef struct kc_llist_node {
	void * data;
	struct kc_llist_node * next;
	struct kc_llist_node * prev;
} kc_llist_node;

// Container for Linked List Nodes.
typedef struct kc_llist {
	kc_llist_node * head;
	kc_llist_node * tail;
} kc_llist;

// Empty a list and free memory.
void kc_llist_free(kc_llist * list);

// Insert item at start of the list.
void kc_llist_add_head(kc_llist * list, void * data);
// Insert item at the end of the list.
void kc_llist_add_tail(kc_llist * list, void * data);

// Remove from the start of the list.
void * kc_llist_remove_head(kc_llist * list);
// Remove from the end of the list.
void * kc_llist_remove_tail(kc_llist * list);

#endif
