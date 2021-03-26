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
	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0b1000001);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, 0b1110001);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE, 0b1111001);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b1001000);
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

//void print_p1(){
//	// 'P1  '
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE, 0b0001100);
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE, 0b1001111);
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0b1111111);
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, 0b1111111);
//}
//
//void print_p2(){
//	// 'P2  '
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE, 0b0001100);
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE, 0b0100100);
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE, 0b1111111);
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE, 0b1111111);
//}

//void start_countdown(){
//	// 'Count down from 5 with HEX0'
//	// 5
////	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b1101110);
////	usleep(1000000);
////	// 4
////	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b0011001);
////	usleep(1000000);
//	// 3
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b0110000);
//	usleep(1000000);
//	// 2
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b0100100);
//	usleep(1000000);
//	// 1
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b1001111);
//	usleep(1000000);
//	// 0
//	IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE, 0b1000000);
//}

int main()
{
	printf("Running..\n");
	FILE* fp;
	char prompt = 0;

	//	Variables
	alt_32 x = 0;
	alt_32 y = 0;
	alt_u16 score = 0b0000000000;
	IOWR(LED_BASE, 0, score);

	// Instantiating the accelerometer SPI (Serial Peripheral Interface).
	// Allows us to interface between the accelerometer and the NIOS II processor
	//	then read data from the accelerometer.
	alt_up_accelerometer_spi_dev * acc_dev;
	acc_dev = alt_up_accelerometer_spi_open_dev ("/dev/accelerometer_spi");

	if ( acc_dev == NULL){
	 	printf ("Error: could not open acc device \n");
	}else{
	  	printf ("Opened acc device \n");
	}

	// Initialize board components with nothing
	reset_hex();
	IOWR(LED_BASE, 0, 0b0000000000);

	// Access stream of data through the jtag_uart in the variable fp
	fp = fopen ("/dev/jtag_uart", "r+"); // r+ opens a file for reading and updating

	if (fp) {
		// 'v' is used as the character to stop the program
		while (prompt != 'v') {
			prompt = getc(fp);
			//	Assign winner if their score reaches 10
			if (prompt == 'w' || score == 0b1111111111){
				print_winner();
				fprintf(fp, "<--> q <--> \n");
				usleep(7000000);
				reset_hex();
				// Reset the LEDs to display nothing
				score = 0b0000000000;
				IOWR(LED_BASE, 0, 0b0000000000);
			//	Assign the loser if an 'l' is sent to their processor
			}else if (prompt == 'l'){
				print_loser();
				fprintf(fp, "<--> q <--> \n");
				usleep(7000000);
				reset_hex();
				// Reset the LEDs to display nothing
				score = 0b0000000000;
				IOWR(LED_BASE, 0, 0b0000000000);
			//	Increment this processor's score after receiving an 'n'
			}else if (prompt == 'n'){ // increment score
				if (score == 0b0000000000){	// handling the initial value
					score = 0b0000000001;
					IOWR(LED_BASE, 0, score); // read the value into the LEDs
				}else{	// general case for incrementing the score
					score <<= 1; // shifting the value to increase the visual score
					score |= 1;	// fill the LSBs with 1s
					IOWR(LED_BASE, 0, score);
				}
			}else if (prompt == 'r'){ // reset the board displays
				// Reset the 7-seg displays to nothing
				reset_hex();
				// Reset the LEDs to display nothing
				score = 0b0000000000;
				IOWR(LED_BASE, 0, 0b0000000000);
	            fprintf(fp, "<--> 0 <--> \n");
	            fprintf(fp, "<--> 0 <--> \n");
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
	printf("Complete\n");
	return 0;
}
