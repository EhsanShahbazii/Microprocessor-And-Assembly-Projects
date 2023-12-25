### Section 1
```c
#include <mega32.h>

#include <delay.h>

void main() {
  DDRA = 0xFF;
  PORTA = 00000000;

  while (1) {
    int i;
    PORTA .0 = 1;
    for (i = 0; i < 8; i++) {
      delay_ms(100);
      PORTA = PORTA << 1;
    }
  }
}
```

### Section 2
```c
#include <mega32.h>

#include <delay.h>

char Data = 0;
char seven_segment[10] = {
  0x7E,
  0x0C,
  0xB6,
  0x9E,
  0xCC,
  0xDA,
  0xFA,
  0x0E,
  0xFE,
  0xDE
};
void main() {
  DDRB = 0xFF;
  PORTB = 0x00;
  while (1) {
    PORTB = seven_segment[Data];
    delay_ms(1000);
    if (Data == 9) {
      Data = 0;
    } else {
      Data++;
    }
  };

}
```

### Section Practice 1
```c
#include <mega32.h>

#include <delay.h>

#include <stdlib.h>

void main() {
  DDRA = 0xFF;
  PORTA = 0x00;

  while (1) {
    int max = 6;
    int min = 0;
    int i;
    for (i = 0; i < 8; i++) {
      int x = (rand() % (max - min + 1)) + min;
      delay_ms(1000);
      PORTA = 0x00;
      PORTA .0 = 1;
      PORTA = PORTA << x;
    }
  }
}
```
