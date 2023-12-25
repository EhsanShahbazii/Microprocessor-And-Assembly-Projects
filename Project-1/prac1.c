#include <mega32.h>
#include <delay.h>
#include <stdlib.h>

void main()
{
    DDRA = 0xFF;
    PORTA = 0x00;
    
    while(1)
    {                 
        int max = 6;
        int min = 0;  
        int i;
        for(i = 0; i < 8; i++)
        {   int x = (rand() % (max - min + 1)) + min;                 
            delay_ms(1000);       
            PORTA = 0x00;
            PORTA.0 = 1;  
            PORTA = PORTA<<x;   
        }
    }  
}