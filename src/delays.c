#include "delays.h"
#define CYCLES_MSEC 1000


void wait_msec(uint32_t msec) {
	for(uint32_t i = 0; i < msec; i++){
		wait_cycles(CYCLES_MSEC);
	}
}


void wait_cycles(uint32_t cycles){
	while(cycles--) {
		asm volatile("nop");
	}
}
