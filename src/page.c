#include <stdio.h>
#include "page.h"
#include "list.h"

struct ppage physical_page_array[128];

struct ppage *free_p = NULL; //track head of list

void init_pfa_list(void) {
	
	free_p = &physical_page_array[0]; //head of list is first element

	for (int i=0; i < 128; i++){
		physical_page_array[i].physical_addr = (void *)(i * 0x200000); //2 mg pages
		
		if (i > 0) {
			list_add((struct list_element**)&free_p, (struct list_element*)&physical_page_array[i]);
							      
//		if (i == 0){
//			physical_page_array[i].prev = NULL;
//		} else {
//			physical_page_array[i].prev = &physical_page_array[i-1];
//		} if ( i == 127) { //at last page
//			physical_page_array[i].next = NULL;
//		} else {
//			physical_page_array[i].next = &physical_page_array[i + 1];
//		}
	}
	}

}


struct ppage *allocate_physical_pages(unsigned int npages) {
	struct ppage *allocate_list = NULL;
	struct ppage *current_p = free_p;
	struct ppage *last_p = NULL;

	while (npages > 0 && current_p != NULL){
		struct ppage *next_p = current_p->next;

		if(allocate_list == NULL){
			allocate_list = current_p;
		} else {
			last_p->next = current_p;
		}
		current_p->prev = last_p;
		last_p = current_p;

		current_p->next = NULL;
		current_p = next_p;
		npages--;
	}

	free_p = current_p;

	if (current_p != NULL){
		current_p->prev = NULL;
	}

	return allocate_list;
}

void free_physical_pages(struct ppage *ppage_list) {
	struct ppage *current_p = ppage_list;

	while (current_p != NULL){
		struct ppage *next_p = current_p->next;

		list_add((struct list_element**)&free_p, (struct list_element*)current_p);
		
//		current_p->next = free_pages;
//		if(free_p != NULL) {
//			free_p->prev = current_p;
//		}
//		current_p->prev = NULL;
//		free_p = current_p;

		current_p = next_p;
	}
}

//}

