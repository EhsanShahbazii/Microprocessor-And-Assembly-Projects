#include <mega32.h>

#include <delay.h>

#include <alcd.h>

#include <stdio.h>

#include <stdlib.h>

#define ADC_VREF_TYPE 0x00
int Data = 0, Data1 = 0;
char Buf[16];
float Din;
unsigned int read_adc(unsigned char adc_input) {
  ADMUX = adc_input | (ADC_VREF_TYPE & 0xff);
  delay_us(10);
  ADCSRA |= 0x40;
  while ((ADCSRA & 0x10) == 0);
  ADCSRA |= 0x10;
  return ADCW;
}
void main(void) {
  PORTB = 0x00;
  DDRB = 0xFF;
  ADMUX = ADC_VREF_TYPE & 0xff;
  ADCSRA = 0x83;
  lcd_init(16);
  lcd_clear();
  lcd_puts("No Data");
  delay_ms(2000);
  while (1) {
    Data = read_adc(0);
    if (Data != Data1) {
      Data1 = Data;
      lcd_clear();
      sprintf(Buf, "Data = %d", Data);
      lcd_puts(Buf);
      lcd_gotoxy(0, 1);
      Din = Data;
      Din = (Din * 5) / 1023;
      ftoa(Din, 2, Buf);
      lcd_putsf("volage=");
      lcd_puts(Buf);
      lcd_puts(Buf);
    }
    delay_ms(1000);
  }
}
