### Section 1
```c
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
```

### Section 2
```c
#include <mega32.h>

#include <delay.h>

#include <alcd.h>

#include <stdio.h>

#include <stdlib.h>

#define ADC_VREF_TYPE 0x00

int Data = 0, Data1 = 0;
char Buf[16];
float volt, amp, oh, temp;
unsigned int adc_rd;

unsigned int read_adc(unsigned char adc_input) {
  ADMUX = adc_input | (ADC_VREF_TYPE & 0xff);
  delay_us(10);
  ADCSRA |= 0x40;
  while ((ADCSRA & 0x10) == 0);
  ADCSRA |= 0x10;
  return ADCW;
}

void voltage() {
  PORTC = 0x00;
  DDRC = 0xFF;
  ADMUX = ADC_VREF_TYPE & 0xFF;
  ADCSRA = 0x83;
  lcd_init(16);
  lcd_clear();
  lcd_putsf("No Data");
  Data = read_adc(0);
  Data1 = Data;
  lcd_clear();
  sprintf(Buf, "Data = %d", Data);
  lcd_puts(Buf);
  lcd_gotoxy(0, 1);
  volt = Data;
  volt = (volt * 5) / 1023;
  ftoa(volt, 2, Buf);
  lcd_putsf("volage = ");
  lcd_puts(Buf);
  lcd_puts(Buf);
  delay_ms(2000);
}

void amper() {
  lcd_init(16);
  lcd_clear();
  ADMUX = 0x01;
  ADCSRA = 0x83;
  Data = read_adc(1);
  amp = Data;
  amp = (amp * 5) / 1023;
  ftoa(amp, 2, Buf);
  lcd_putsf("Amper = ");
  lcd_puts(Buf);
  lcd_puts(Buf);
  delay_ms(2000);
}

void ohm() {
  lcd_init(16);
  lcd_clear();
  adc_rd = read_adc(2); 
  temp = (adc_rd * .00488281); 
  oh = ((1000 * (temp / 5)) / (1 - (temp / 5))); 
  ftoa(oh, 2, Buf); 
  lcd_puts(Buf);
  delay_ms(2000);
}

void main(void) {
  DDRB = 0xFF;
  while (1) {
    if (PINB .0 == 0 && PINB .1 == 0) {
      voltage();
    } else if (PINB .0 == 0 && PINB .1 == 1) {
      amper();
    } else if (PINB .0 == 1 && PINB .1 == 0) {
      ohm();
    } else {
      lcd_init(16);
      lcd_clear();
      lcd_putsf("Select Op!!!");
      delay_ms(2000);
    }
  }
}
```
