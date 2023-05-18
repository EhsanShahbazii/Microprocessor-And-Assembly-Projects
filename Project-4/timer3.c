#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>
char Buf[16];
unsigned char Counter=0;
unsigned int Data;
interrupt [TIM0_OVF] void timer0_ovf_isr(void) {
Counter++;}
void main(){
TCCR0=0x07;//Timer0 in Normal mode, External Clock
TIMSK=0x01;
DDRB.3=1;// PORTB.3 as Output
lcd_init(16);
lcd_clear();
lcd_puts("Start");
#asm("sei")
while(1){
TCCR0=0x00;
TCNT0=0x00;
Counter = 0;
TIFR = 0x01;
TCCR0=0x07;
delay_ms(1000);
TCCR0=0x00;
Data = (Counter * 256) + TCNT0;
sprintf(Buf,"Freq = %d",Data);
lcd_clear();
lcd_puts(Buf);
}}