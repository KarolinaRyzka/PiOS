
#include <stdio.h>
#include "rprintf.h"
#include "mmu.h"

char glbl[128];

unsigned long get_timer_count() {
	volatile unsigned long *timer_count_register = (volatile unsigned long *) 0x3f003004; //cast as long pointer
	return *timer_count_register;
}

void delay1ms() {
	unsigned long start = get_timer_count(); //store timer count in start
	while (get_timer_count() - start < 1000) { //loop until 1000 microseconds or 1 millisecond
	}
}


void kernel_main() {

    extern unsigned int __bss_start;
    extern unsigned int __bss_end;
    char *bssstart, *bssend;

    bssstart = (char *)&__bss_start;
    bssend = (char *)&__bss_end;

    //write for loop to set memory values to 0 in between bssstart and bssend
    while (bssstart < bssend) {
       *bssstart = 0;
	bssstart++;
    }

   // unsigned long start = get_timer_count(); //start time
    delay1ms(); //call function
   // unsigned long end = get_timer_count(); //end time
   
    mapPages((void*)0x0, (void*)0x0);
   
    while(1){
    }
}

