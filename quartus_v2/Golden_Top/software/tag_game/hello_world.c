/** "Hello World" example.
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

#include <stdio.h>
#include <string.h>
#include "system.h"
#include "altera_up_avalon_accelerometer_spi.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include <stdlib.h>
#include <sys/alt_stdio.h>

char activegame(FILE* fp, alt_32 x, alt_32 y)
{
    alt_32 radius = 50;

	if((abs(x) > abs(y)) && (abs(x) > radius)){
		if(x > 0){
		   	fprintf(fp, "<--> A <--> \n");
		}else{
		   	fprintf(fp, "<--> D <--> \n");
		}
	}else if(abs(y) > radius){
		if( y > 0){
			fprintf(fp, "<--> S <--> \n");
		}else{
			fprintf(fp, "<--> W <--> \n");
		}
	}else{
		fprintf(fp, "<--> No movement <--> \n");
	}
	fprintf(fp, "<--> END <--> \n %c", 0x4);
}

int main()
{
	printf("Running..\n");
	FILE* fp;
	char prompt = 0;
	char output;

	alt_32 x = 0;
	alt_32 y = 0;
	alt_16 radius = 50;

	alt_up_accelerometer_spi_dev * acc_dev;
	acc_dev = alt_up_accelerometer_spi_open_dev ("/dev/accelerometer_spi");

	if ( acc_dev == NULL){
	 	printf ("Error: could not open acc device \n");
	}else{
	  	printf ("Opened acc device \n");
	}

	// Access stream of data through the jtag_uart in the variable fp
	fp = fopen ("/dev/jtag_uart", "r+"); // r+ opens a file for reading and updating

	if (fp) {
		// here 'v' is used as the character to stop the program
		while (prompt != 'v') {
			// accept the character that has been sent down
			do prompt = getc(fp); while (prompt == -1);
			if (prompt != 'v' && prompt != '\xff') {
				alt_up_accelerometer_spi_read_x_axis(acc_dev, &x);
				alt_up_accelerometer_spi_read_y_axis(acc_dev, &y);

				activegame(fp, x, y);
			}
			if (ferror(fp)) {
				clearerr(fp);
			}
		}

		// fprintf(fp, "Closing the JTAG UART file handle.\n %c",0x4);
		fclose(fp);
	}

	printf("Complete\n");

	return 0;
}

