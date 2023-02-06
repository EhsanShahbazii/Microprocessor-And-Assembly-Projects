#include <mega32.h>
#include <delay.h>

char Data = 0;
char seven_segment[10] = {0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0x0E, 0xFE, 0xDE};
void main()
{
    DDRB = 0xFF;
    PORTB = 0x00;
    while (1) {    
        PORTB = seven_segment[Data];
        delay_ms(1000);
        if (Data == 9){
            Data = 0;
        } else {
            Data++;
        }    
    };

}