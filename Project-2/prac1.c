#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

char Data;
char Buf[32];
int x = 0;

void main() {
    DDRC.0 = 1;
    lcd_init(16);
    lcd_clear();
    lcd_puts("Start");
    delay_ms(2000);
    lcd_clear();
    while(1){   
        lcd_gotoxy(0,0);
        lcd_puts("Counting");  
        lcd_gotoxy(0,1);    
        
        while(x != 100){           
              lcd_gotoxy(0,0);
              lcd_puts("Counting");  
              lcd_gotoxy(0,1);          
              sprintf(Buf,"%d.%d",Data, x);    
              
               if(PINC.0 == 0){
                  x++;
               }else x--; 
               
               if(x == 0) break;       
               
              lcd_puts(Buf);                 
              delay_ms(10);
              lcd_clear();
        }
        
        if(x == 100){
          x = 0;  
        }else x = 99;   
        
        if(PINC.0 == 0){
           Data++;
        }else Data--;     
         
        sprintf(Buf,"%d.%d",Data, x);
        lcd_puts(Buf);        
        delay_ms(10);
        lcd_clear();
    }
}