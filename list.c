#include <stdio.h>
#include "list.h"

void list_add(struct list_element *list_head, struct list_element *new_element) {
	new_element->next = *list_head;
	*list_head = new_element;
}

void list_remove(struct list_element *element){
	struct list_element *current = *list_head;
	struct list_element *prev = NULL;

	if (current == element) {
		*list_head = current->next;
		return;
	}

	while (current != NULL && current != element) {
		prev = current;
		current = current->next;
	}

	if (current == element) {
		prev->next = current->next;
	}
}

int main(){
	struct list_element c = {NULL, 0}; //next ptr is NULL, end of list
	struct list_element b = {&c, 0}; //next ptr points to c
	struct list_element a = {&b, 0}; //next ptr points to a
	struct list_element *head = &a;
	}	
