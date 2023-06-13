### Section 1
```c
#include <mega32.h>

#include <delay.h>

#include <alcd.h>

#include <stdio.h>

char Buf[16];
char Din, Count = 0;
void main(void) {
  UCSRA = 0x00;
  UCSRB = 0x10;
  UCSRC = 0xA6;
  UBRRH = 0x00;
  UBRRL = 0x0C;
  lcd_init(16);
  lcd_clear();
  lcd_puts("No Data");
  delay_ms(2000);
  while (1) {
    Din = getchar();
    lcd_clear();
    lcd_puts("Input = ");
    lcd_putchar(Din);
    lcd_gotoxy(0, 1);
    sprintf(Buf, "Count = %d", Count);
    lcd_puts(Buf);
    Count++;
  }
}
```

### Section Practice 1
```c
#include <mega32.h>


#define DATA_REGISTER_EMPTY(1 << UDRE)
#define RX_COMPLETE(1 << RXC)
#define FRAMING_ERROR(1 << FE)
#define PARITY_ERROR(1 << UPE)
#define DATA_OVERRUN(1 << DOR)

#define TX_BUFFER_SIZE 8
char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE <= 256
unsigned char tx_wr_index = 0, tx_rd_index = 0;
#else
unsigned int tx_wr_index = 0, tx_rd_index = 0;
#endif

#if TX_BUFFER_SIZE < 256
unsigned char tx_counter = 0;
#else
unsigned int tx_counter = 0;
#endif

interrupt[USART_TXC] void usart_tx_isr(void) {
  if (tx_counter) {
    --tx_counter;
    UDR = tx_buffer[tx_rd_index++];
    #if TX_BUFFER_SIZE != 256
    if (tx_rd_index == TX_BUFFER_SIZE) tx_rd_index = 0;
    #endif
  }
}

#ifndef _DEBUG_TERMINAL_IO_
#define _ALTERNATE_PUTCHAR_
#pragma used +
  void putchar(char c) {
    while (tx_counter == TX_BUFFER_SIZE);
    #asm("cli")
    if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY) == 0)) {
      tx_buffer[tx_wr_index++] = c;
      #if TX_BUFFER_SIZE != 256
      if (tx_wr_index == TX_BUFFER_SIZE) tx_wr_index = 0;
      #endif
      ++tx_counter;
    } else
      UDR = c;
    #asm("sei")
  }
#pragma used -
  #endif

#include <stdio.h>

#include <delay.h>

#define MYUBRR F_CPU / 16 / BAUD - 1
#define F_CPU 8000000 UL
#define BAUD 4800

void USART_Init(unsigned int ubrr) {
  /*Set baud rate */
  UBRRH = (unsigned char)(ubrr >> 8);
  UBRRL = (unsigned char) ubrr;
  UCSRB = (1 << RXEN) | (1 << TXEN);
  UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}

void USART_Transmit(unsigned char data) {
  while (!(UCSRA & (1 << UDRE)));
  UDR = data;
  DDRA .0 = 1;
  PORTA .0 = 1;
}

void main(void) {
  USART_Init(MYUBRR); 
  DDRC = 0x00;
  while (1) {
    if (PINC .0 == 1) {
      USART_Transmit('A'); 
    } else if (PINC .1 == 1) {
      USART_Transmit('B');
    }
  }
}
```
