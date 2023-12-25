### Section 1
```c
#include <mega32.h>

void main() {
  TCCR0 = 0x6A;
  OCR0 = 0x7F;
  DDRB .3 = 1;
  while (1) {}
}
```

### Section 2
```c
#include <mega32.h>

void main() {
  TCCR0 = 0x62;
  OCR0 = 0x7F;
  DDRB .3 = 1;
  while (1) {}
}
```

### Section 3
```c
#include <mega32.h>

#include <alcd.h>

#include <delay.h>

#include <stdio.h>

char Buf[16];
unsigned char Counter = 0;
unsigned int Data;
interrupt[TIM0_OVF] void timer0_ovf_isr(void) {
  Counter++;
}
void main() {
  TCCR0 = 0x07;
  TIMSK = 0x01;
  DDRB .3 = 1;
  lcd_init(16);
  lcd_clear();
  lcd_puts("Start");
  #asm("sei")

  while (1) {
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    Counter = 0;
    TIFR = 0x01;
    TCCR0 = 0x07;
    delay_ms(1000);
    TCCR0 = 0x00;
    Data = (Counter * 256) + TCNT0;
    sprintf(Buf, "Freq = %d", Data);
    lcd_clear();
    lcd_puts(Buf);
  }
}
```

### Section Practice 1
```c
#include <delay.h>

#include <mega32.h>

void main() {

  int count = 0;
  DDRC .0 = 1; 
  TCNT0 = 6; 
  TCCR0 = 0x02;

  while (1) {
    if (TIFR & 0x01) {
      TIFR = 0x01;
      TCNT0 = 6;
      count++;
    }

    if (count >= 500) {
      PORTC .0 = ~PORTC .0;
      count = 0;
    }
  }
}
```
