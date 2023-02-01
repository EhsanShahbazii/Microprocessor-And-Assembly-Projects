#include <mega32.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF;
    PORTA = 00000000;
    
    while(1)
    {                   
        int i;
        PORTA.0 = 1;    
        for(i = 0; i < 8; i++)
        {                    
            delay_ms(100);
            PORTA = PORTA<<1;   
        }
    }  
}