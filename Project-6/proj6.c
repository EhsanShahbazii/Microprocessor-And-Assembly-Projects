#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
char Buf[16];
char Din,Count=0;
void main(void) {
    UCSRA=0x00;
    UCSRB=0x10;
    UCSRC=0xA6;
    UBRRH=0x00;
    UBRRL=0x0C;
    lcd_init(16);
    lcd_clear();
    lcd_puts("No Data");
    delay_ms(2000);
    while (1){
        Din = getchar();
        lcd_clear();
        lcd_puts("Input = ");
        lcd_putchar(Din);
        lcd_gotoxy(0,1);
        sprintf(Buf,"Count = %d",Count);
        lcd_puts(Buf);
        Count++;
}}