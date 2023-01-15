#include <stdlib.h>
#include "kc/llist.h"

void kc_llist_free(kc_llist * list) {
	int i = 0;
	while (list->head) {
		kc_llist_node * current = list->head;
		list->head = current->next;

		free(current->data);
		free(current);
	}
}

void kc_llist_add_head(kc_llist * list, void * data) {
	kc_llist_node * node = (kc_llist_node *) malloc(sizeof(kc_llist_node));
	node->data = data;
	node->next = list->head;
	node->prev = NULL;

	if (list->head) {
		list->head->prev = node;
	}

	if (!list->tail) {
		list->tail = node;
	}

	list->head = node;
}

void kc_llist_add_tail(kc_llist * list, void * data) {
	kc_llist_node * node = (kc_llist_node *) malloc(sizeof(kc_llist_node));
	node->data = data;
	node->prev = list->tail;
	node->next = NULL;

	if (list->tail) {
		list->tail->next = node;
	}

	if (!list->head) {
		list->head = node;
	}

	list->tail = node;
}

void * kc_llist_remove_head(kc_llist * list) {
	kc_llist_node * node = list->head;
	if (!node) {
		return NULL;
	}

	list->head = node->next;
	if (!list->head) {
		list->tail = NULL;
	}

	void * data = node->data;
	free(node);

	return data;
}

void * kc_llist_remove_tail(kc_llist * list) {
	kc_llist_node * node = list->tail;
	if (!node) {
		return NULL;
	}

	list->tail = node->prev;
	if (!list->tail) {
		list->head = NULL;
	}

	void * data = node->data;
	free(node);

	return data;
}
