### Section 1
```c
#include <mega32.h>

#include <delay.h>

#include <alcd.h>

char Data;
void main() {
  lcd_init(16);
  lcd_clear();
  while (1) {
    lcd_gotoxy(0, 0);
    lcd_putchar(Data + 48);
    if (Data == 9) Data = 0;
    else Data++;
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

char Data;
char Buf[32];

void main() {
  lcd_init(16);
  lcd_clear();
  lcd_puts("Start");
  delay_ms(5000);
  lcd_clear();
  while (1) {
    sprintf(Buf, "%d", Data);
    lcd_puts("Counting");
    lcd_gotoxy(0, 1);
    lcd_puts(Buf);
    Data++;
    delay_ms(1000);
    lcd_clear();
  }
}
```

### Section Practice 1
```c
#include <mega32.h>

#include <delay.h>

#include <alcd.h>

#include <stdio.h>

char Data;
char Buf[32];
int x = 0;

void main() {
  DDRC .0 = 1;
  lcd_init(16);
  lcd_clear();
  lcd_puts("Start");
  delay_ms(2000);
  lcd_clear();
  while (1) {
    lcd_gotoxy(0, 0);
    lcd_puts("Counting");
    lcd_gotoxy(0, 1);

    while (x != 100) {
      lcd_gotoxy(0, 0);
      lcd_puts("Counting");
      lcd_gotoxy(0, 1);
      sprintf(Buf, "%d.%d", Data, x);

      if (PINC .0 == 0) {
        x++;
      } else x--;

      if (x == 0) break;

      lcd_puts(Buf);
      delay_ms(10);
      lcd_clear();
    }

    if (x == 100) {
      x = 0;
    } else x = 99;

    if (PINC .0 == 0) {
      Data++;
    } else Data--;

    sprintf(Buf, "%d.%d", Data, x);
    lcd_puts(Buf);
    delay_ms(10);
    lcd_clear();
  }
}
```

### Section Practice 2
```c
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

  while (1) {
    int i;
    for (i = 0; i < 15; i++) {
      lcd_gotoxy(0, 0);
      lcd_puts("Counting");
      lcd_gotoxy(i, 1);
      sprintf(Buf, "%d", Data);
      lcd_puts(Buf);
      delay_ms(1000);
      Data++;
      lcd_clear();
    }
    Data -= 2;
    for (i = 13; i > 0; i--) {
      lcd_gotoxy(0, 0);
      lcd_puts("Counting");
      lcd_gotoxy(i, 1);
      sprintf(Buf, "%d", Data);
      lcd_puts(Buf);
      Data--;
      delay_ms(1000);
      lcd_clear();
    }
  }
}
```
