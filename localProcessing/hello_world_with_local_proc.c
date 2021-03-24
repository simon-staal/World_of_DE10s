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

// This function reads the current x-axis and y-axis values. It then
//	calculates the position the board is directed to then outputs the
//	direction in the form of WASD and the diagonal directions e.g.
//	TL = Top Left, BR = Bottom Right (when looking at the board from
//	an eagle view)

/*
char activegame(FILE* fp, alt_32 x, alt_32 y)
{
    alt_32 radius = 50;

    // fprintf(fp, "<--> x : %d, y : %d <--> \n", x, y);

    // Values chosen must perfectly align with adjacent characters to ensure no dead zones

	if((abs(x) > abs(y)) && (abs(x) > radius)){ // BR
		if(x > 0 && abs(y) <= 20){
		   	fprintf(fp, "<--> A <--> \n");
		}else if(x < -radius && abs(y) <= 25){
		   	fprintf(fp, "<--> D <--> \n");
		}else if((x < -15) && y < -25){
		   	fprintf(fp, "<--> TR <--> \n");
		}else if(x < -15 && y > 25){
			fprintf(fp, "<--> BR <--> \n");
		}else if((x > 25) && y > 20){
		   	fprintf(fp, "<--> BL <--> \n");
		}else if((x > 25) && (y < -20)){
		   	fprintf(fp, "<--> TL <--> \n");
		}
	}else if(abs(y) > radius){ // TL, TR, BL
		if( abs(x) <= 25 && y > 0){
			fprintf(fp, "<--> S <--> \n");
		}else if((abs(x) <= 25) && (y < -radius)){
			fprintf(fp, "<--> W <--> \n");
		}else if((x > 25) && (y < -20)){
		   	fprintf(fp, "<--> TL <--> \n");
		}else if((x < -25) && y < -25){
		   	fprintf(fp, "<--> TR <--> \n");
		}else if((x > 25) && y > 20){
		   	fprintf(fp, "<--> BL <--> \n");
		}else if(x < -25 && y > 25){
			fprintf(fp, "<--> BR <--> \n");
		}
	}else{
		fprintf(fp, "<--> No movement <--> \n");
	}
	fprintf(fp, "<--> END <--> \n %c", 0x4);
}
*/

int main()
{
	printf("Running..\n");
	FILE* fp;
	char prompt = 0;

	alt_32 x = 0;
	alt_32 y = 0;

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
                fprintf(fp, "<--> %d <--> \n", x);
				alt_up_accelerometer_spi_read_y_axis(acc_dev, &y);
                fprintf(fp, "<--> %d <--> \n", y);
                fprintf(fp, "<--> END <--> \n %c", 0x4);

				// activegame(fp, x, y);
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
