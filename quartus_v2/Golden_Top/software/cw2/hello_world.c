/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <sys/alt_stdio.h>
#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <unistd.h>
#include <stdlib.h>

int main()
{
/*	int switch_datain;
	while(1){
		switch_datain= ~IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE);
		if (switch_datain == 0b01){
			IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE,0b1001000);
		}
	}

	printf("Hello from Nios II!\n");
*/
	int switch_datain;
	int switch_datain_temp;
	alt_putstr("Hello from Nios II!\n");

	// Event loop never exits.
	while (1){
	  switch_datain= ~IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE);
	  // this temp stores the input button value for the 2nd LED
	  switch_datain_temp = switch_datain;
	  // capture HEX1 and set it to LEDR4
	  switch_datain &= (0b0000000010);
	  switch_datain <<= 3;

	  // capture HEX0 and set it to LEDR10
	  switch_datain_temp &= (0b0000000001);
	  switch_datain_temp <<= 9;

	  switch_datain |= switch_datain_temp;

	  IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE,switch_datain);

	}
  return 0;
}
