#include <stdio.h>
#include "list.h"

void list_add(struct list_element *list_head, struct list_element *new_element) {
	new_element->next = *list_head; //make next pointer of new element point to the head
	*list_head = new_element; //make new element head of list (adding to beginning)
}

void list_remove(struct list_element *element){

	if (element == NULL) { //if element is null
		return;
	}

	if (element->next == NULL) { //if element is last, it is already pointing at null so it is disconnected
		return;
	}


	struct list_element *next_element = element->next; //pointer that point the current element to the next
	element->data = next_element->data; //copy data into current element from next
	element->next = next_element->next; //point to element after the next (skipping next element)

}

int main(){
	struct list_element c = {NULL, 0}; //next ptr is NULL, end of list
	struct list_element b = {&c, 0}; //next ptr points to c
	struct list_element a = {&b, 0}; //next ptr points to a
	struct list_element *head = &a;
	}	
