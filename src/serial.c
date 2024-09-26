
#include <stdio.h>
#include "rprintf.h"
#define MU_IO ((volatile unsigned int *)0xFE215040) //for raspberry pi

extern int getEL();

void myputc(int data) {
	*MU_IO = (unsigned int)data; //accessing memory at this address, put data there

}


void main() {
	esp_printf(myputc, "Execution level is: %d\r\n", getEL());
}



