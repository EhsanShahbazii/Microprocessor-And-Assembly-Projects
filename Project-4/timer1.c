#include <mega32.h>
void main(){
TCCR0=0x6A;//Timer0 in Non-Inverting FAST PWM mode, Prescaler 8
OCR0=0x7F;
DDRB.3=1;// PORTB.3 as Output
while(1){
}}