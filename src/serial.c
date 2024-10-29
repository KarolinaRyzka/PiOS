#include "serial.h"
#include <stdio.h>
#include <stdint.h>
#include "rprintf.h"
#define MU_IO ((volatile unsigned int *)0xFE215040) //for raspberry pi

extern int getEL();


void uart_send(char data) {
	*MU_IO = (unsigned int)data; //accessing memory at this address, put data there

}

void uart_puts(const char *str) {
	while (*str) {
		uart_send(*str++);
	}
}

/*
void main() {
	esp_printf(myputc, "Execution level is: %d\r\n", getEL());
}
*/


