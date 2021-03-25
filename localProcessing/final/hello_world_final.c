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


void reset_hex(){
	IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE, 0b1111111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE, 0b1111111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0b1111111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, 0b1111111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, 0b1111111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b1111111);
}

void print_winner(){
	// 'U WIN '
	IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE, 0b1000001);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE, 0b1111111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0b1100010);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, 0b1001111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, 0b1001000);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b1111111);
}

void print_loser(){
	// 'U LOSE'
	IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE, 0b1000001);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE, 0b1111111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0b1000111);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, 0b1000000);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, 0b0010010);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b0000110);
}

int main()
{
	printf("Running..\n");
	FILE* fp;
	char prompt = 0;

	//	Variables
	alt_32 x = 0;
	alt_32 y = 0;
	alt_u16 score = 0b0000000000;

	// Instantiating the accelerometer values
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
			// accept the character that has been sent down and increment to the
			//	next character
			do prompt = getc(fp); while (prompt == -1);
			if (prompt != 'v' && prompt != '\xff') {
				//	Assign winner if their score reaches 10
				if (prompt == 'w' || score == 0b1111111111){
					print_winner();
				//	Assign the loser if an 'l' is sent to their processor
				}else if (prompt == 'l'){
					print_loser();
				//	Increment this processor's score after receiving an 'n'
				}else if (prompt == 'n'){ // increment score
					if (score == 0b0000000000){	// handling the initial value
						score = 0b0000000001;
						IOWR(LED_BASE, 0, score); // read the value into the LEDs
					}else{
						score <<= 1; // shifting the value to increase the visual score
						score |= 1;	// fill the LSBs with 1s
						IOWR(LED_BASE, 0, score);
					}
				}
				else{
					// if a generic character is sent, print nothing to the hex digits
					reset_hex();
				}

					// Button management
				int button_datain= ~IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE);
				button_datain &= 0b11;

				if(button_datain == 1){ // Fire guns, top button
					fprintf(fp, "<--> e <--> \n %c", 0x4);
				}else if(button_datain == 2){ // Throw bomb, bottom button
					fprintf(fp, "<--> r <--> \n %c", 0x4);
				}

					// Read accelerometer values then print to the nios ii terminal
				// x-axis value
				alt_up_accelerometer_spi_read_x_axis(acc_dev, &x);
                fprintf(fp, "<--> %i <--> \n", x);
                // y-axis value
				alt_up_accelerometer_spi_read_y_axis(acc_dev, &y);
                fprintf(fp, "<--> %i <--> \n", y);
                fprintf(fp, "<--> END <--> \n %c", 0x4);

			}
			if (ferror(fp)) {
				clearerr(fp);
			}
		}
		fclose(fp);
	}

	printf("Complete\n");

	return 0;
}
