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
#include <time.h>

void reset_hex(){
	// Resets the 7-segment displays to show nothing
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

int main()
{
    /*
        Timing structure
        start = clock();
        
        < Insert your code you are timing here >

        end = clock();
        double dif = (end - start) / CLOCKS_PER_SEC;
        fprintf(fp, "Time taken to <perform this section of the code>: %d seconds \n", dif);
        https://stackoverflow.com/questions/5248915/execution-time-of-c-program
    */

	printf("Running..\n");
	FILE* fp;
	char prompt = 0;

	//	Variables
	alt_32 x = 0;
	alt_32 y = 0;
	alt_u16 score = 0b0000000000;
	IOWR(LED_BASE, 0, score);

    // Timing variables
    clock_t start;
    clock_t end;

	// Instantiating the accelerometer SPI (Serial Peripheral Interface).
	// Allows us to interface between the accelerometer and the NIOS II processor
	//	then read data from the accelerometer.
    start = clock();
	alt_up_accelerometer_spi_dev * acc_dev;
	acc_dev = alt_up_accelerometer_spi_open_dev ("/dev/accelerometer_spi");
    end = clock();
	double dif = (end - start) / CLOCKS_PER_SEC;
    fprintf(fp, "<--> Time taken to connect to SPI: %d seconds <-->\n", dif);

	// Check if the SPI has been instantiated properly
	if ( acc_dev == NULL){
	 	printf ("Error: could not open acc device \n");
	}else{
	  	printf ("Opened acc device \n");
	}

	// Initialize board components with nothing
	// 7-segment displays
    start = clock();
	reset_hex();
    end = clock();
    double dif = (end - start) / CLOCKS_PER_SEC;
    fprintf(fp, "<--> Time taken to call reset_hex(): %d seconds <--> \n", dif);

	// LEDs
	IOWR(LED_BASE, 0, 0b0000000000);

	// Access stream of data through the jtag_uart in the variable fp
    start = clock();
	fp = fopen ("/dev/jtag_uart", "r+"); // r+ opens a file for reading and updating
    end = clock();
    double dif = (end - start) / CLOCKS_PER_SEC;
    fprintf(fp, "<--> Time taken to open JTAG UART path: %d seconds <--> \n", dif);

	// If the file path was successfully opened
	if (fp) {
		// 'v' is used as the character to stop the program
		while (prompt != 'v') {
			prompt = getc(fp);
			//	Assign winner if their score reaches 10
			if (score == 0b1111111111){
                start = clock();
				print_winner();
                end = clock();
                double dif = (end - start) / CLOCKS_PER_SEC;
                fprintf(fp, "<--> Time taken to print winner: %d seconds <--> \n", dif);

				// Character with no effect to avoid error
				fprintf(fp, "<--> q <--> \n");
				// Keep 'U WIN' message up for 7 seconds
				usleep(7000000);
				// Reset the on-board components for a new round of the game
				reset_hex();
				score = 0b0000000000;
				IOWR(LED_BASE, 0, 0b0000000000);
			//	Assign the loser if an 'l' is sent to their processor
			}else if (prompt == 'l'){
				// Same setup as print_winner() scope but for print_loser()
                end = clock();
				print_loser();
                end = clock();
                double dif = (end - start) / CLOCKS_PER_SEC;
                fprintf(fp, "<--> Time taken to print loser: %d seconds <--> \n", dif);

				fprintf(fp, "<--> q <--> \n");
				usleep(7000000);
				reset_hex();
				// Reset the LEDs to display nothing
				score = 0b0000000000;
				IOWR(LED_BASE, 0, 0b0000000000);
			//	Increment this processor's score after receiving an 'n'
			}else if (prompt == 'n'){ // increment score
				// handling the initial value
				if (score == 0b0000000000){	
					score = 0b0000000001;
					// read the value into the LEDs
					IOWR(LED_BASE, 0, score);
				}else{	// general case for incrementing the score
					// shifting the value to increase the visual score on the LEDs
                    start = clock();
					score <<= 1;
					// fill the LSBs with 1s
					score |= 1;
					// write the updated value to the LEDs
					IOWR(LED_BASE, 0, score);
                    end = clock();
                    double dif = (end - start) / CLOCKS_PER_SEC;
                    fprintf(fp, "<--> Time taken to increment score: %d seconds <--> \n", dif);
				}
			}else if (prompt == 'r'){ // reset the board displays, used at the start of the game
				start = clock();
                // Reset the 7-seg displays to nothing
				reset_hex();
				// Reset the LEDs to display nothing
				score = 0b0000000000;
				IOWR(LED_BASE, 0, 0b0000000000);

                end = clock();
                double dif = (end - start) / CLOCKS_PER_SEC;
                fprintf(fp, "<--> Time taken to reset everything: %d seconds <--> \n", dif);
				// Useless output characters used to output nothing
	            fprintf(fp, "<--> 0 <--> \n");
	            fprintf(fp, "<--> 0 <--> \n");
			}

			// 		Button management
            start = clock();
			int button_datain= ~IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE);
			button_datain &= 0b11;
            end = clock();
            double dif = (end - start) / CLOCKS_PER_SEC;
            fprintf(fp, "<--> Time taken to read button value: %d seconds <--> \n", dif);

			if(button_datain == 1){ // Fire guns, top button
				fprintf(fp, "<--> e <--> \n");
			}else if(button_datain == 2){ // Throw bomb, bottom button
				fprintf(fp, "<--> r <--> \n");
			}

				// Read accelerometer values then print to the Nios II terminal
			// x-axis value
            start = clock();
			alt_up_accelerometer_spi_read_x_axis(acc_dev, &x);
            end = clock();
            double dif = (end - start) / CLOCKS_PER_SEC;
            fprintf(fp, "<--> Time taken to read x-axis: %d seconds <--> \n", dif);

            fprintf(fp, "<--> %i <--> \n", x);

            // y-axis value
            start = clock();
			alt_up_accelerometer_spi_read_y_axis(acc_dev, &y);
            end = clock();
            double dif = (end - start) / CLOCKS_PER_SEC;
            fprintf(fp, "<--> Time taken to read y-axis: %d seconds <--> \n", dif);

            fprintf(fp, "<--> %i <--> \n", y);
			// Output a 0x4 to indicate the end of the character stream;
			// same as doing CTRL + D in the NIOS II terminal. Needed to 
			// output characters to the JTAG UART stream.
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
