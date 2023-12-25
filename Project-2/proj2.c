#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

char Data;
char Buf[32];

void main() {
    lcd_init(16);
    lcd_clear();
    lcd_puts("Start");
    delay_ms(5000);
    lcd_clear();
    while(1){
        sprintf(Buf,"%d",Data);
        lcd_puts("Counting");
        lcd_gotoxy(0,1);
        lcd_puts(Buf);
        Data++;
        delay_ms(1000);
        lcd_clear();
    }
}