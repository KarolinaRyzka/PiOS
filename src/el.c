#include <stdio.h>

unsigned int getEL(void){
	unsigned int el;
	asm volatile(
		"mrs %0, CurrentEL\n"
		"lsr %0, %0, #2\n" //shift right by two since padded w  zeroes
		: "=r" (el)
	);
	return el;
}
