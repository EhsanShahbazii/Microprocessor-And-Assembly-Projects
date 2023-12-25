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
    delay_ms(2000);
    lcd_clear();   
        
    while(1){
        int i;
        for(i = 0; i < 15; i++){
            lcd_gotoxy(0,0);
            lcd_puts("Counting");  
            lcd_gotoxy(i,1);
            sprintf(Buf,"%d",Data);
            lcd_puts(Buf);        
            delay_ms(1000);
            Data++;
            lcd_clear();
        }  
        Data -= 2;
        for(i = 13; i > 0; i--){
            lcd_gotoxy(0,0);
            lcd_puts("Counting");  
            lcd_gotoxy(i,1); 
            sprintf(Buf,"%d",Data);
            lcd_puts(Buf);         
            Data--;
            delay_ms(1000);  
            lcd_clear();
        }     
    }
}