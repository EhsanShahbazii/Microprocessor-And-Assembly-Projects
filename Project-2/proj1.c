
#include <mega32.h>
#include <delay.h>
#include <alcd.h>
char Data;
void main(){
    lcd_init(16);
    lcd_clear();
        while(1){
            lcd_gotoxy(0,0);
            lcd_putchar(Data+48);
            if(Data == 9) Data = 0;
            else Data++;
            delay_ms(1000);
        }
}