#include <delay.h>
#include <mega32.h>
void main()

{

    int count=0;

    DDRC.0=1; // set o/p mode

    TCNT0=6; // initialize the timer

    TCCR0=0x02; // 8 prescalar if no prescalar accuracy is much more

    while(1){

        if(TIFR & 0x01) // we will enter here after every 4us
        {
            TIFR=0x01; // clear the flag

            TCNT0=6;

            count++;

        }

        if(count>=500) // (500 count = 1s)
        {
            PORTC.0=~PORTC.0;

            count=0;
        }
    }
}