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

void startgame();

int activegame();

int absolute();


int main()
{

    activegame();



    return 0;
}


int activegame()
{
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

    while(1){


        alt_up_accelerometer_spi_read_x_axis(acc_dev, &x);
        alt_up_accelerometer_spi_read_y_axis(acc_dev, &y);


        if((abs(x) > abs(y)) && (abs(x) > radius)){

            if(x > 0){
                printf("a");
            }else{
                printf("d");
            }

        }else if(abs(y) > radius){

            if( y > 0){
                printf("s");
            }else{
                printf("w");
            }
       }


       usleep(10000); // 0.1sec
       printf("\n");
    }
}