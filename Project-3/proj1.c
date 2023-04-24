#include <mega32.h>
#include <delay.h>
#include <stdio.h>
#include <bcd.h>

unsigned char scan[4]={0XFE,0XFD,0XFB,0XF7};
char Key, State=0, Operand;
int Num0=0, Num1=0, Result;
char arrkey[16]={
'7','8','9','/',
'4','5','6','*',
'1','2','3','-',
'C','0','=','+'};

#define c1 PINB.4
#define c2 PINB.5
#define c3 PINB.6
#define c4 PINB.7
#define keypad_port PORTB

char keypad(){
    unsigned char r,c,k;
    DDRB=0X0F;
    keypad_port=0XFF;
    while(1){
        for (r=0; r<4; r++){
            c=255;
            keypad_port=scan[r];
            delay_us(10);
            if(c1==0) c=0; if(c2==0) c=1; if(c3==0) c=2; if(c4==0) c=3;
            if (c!=255){
            k=arrkey[(r*4)+c];
            while(c1==0); while(c2==0); while(c3==0); while(c4==0);
            delay_ms(50);
            return k;
            }
        }
    }
}

void main(void){
    DDRC = 0XFF;
    PORTC = 0b00000000;
    
    while (1){
        Key=keypad();
        switch (State) {
            case 0:
            if (Key == 'C') {
                Num0=0; Num1=0; Operand=''; PORTC = 0XFF;
            }         
            else if ((Key == '+') | (Key == '-') | (Key == '/') | (Key == '*')) {
                Operand = Key; State =1;
            }
            else {
                Num1 = Num1 * 10 + Key - 48; 
            }
            break;
            
            case 1:
            if (Key == 'C') {
                Num0=0; Num1=0; Operand=''; State = 0; PORTC = 0;
            }
            else if ((Key == '1') | (Key == '2') | (Key == '3') | (Key == '4')
            | (Key == '5') | (Key == '6') | (Key == '7') | (Key == '8')
            | (Key == '9') | (Key == '0')) {
                Num0 = Num0 * 10 + Key - 48; 
            }
            else if (Key == '='){
                if (Operand == '+') {
                    Result = Num1 + Num0;                      
                    PORTC = bin2bcd(Result);
                }
                else if (Operand == '-') {
                    Result = Num1 - Num0; PORTC = bin2bcd(Result);
                }
                else if (Operand == '/') {
                    if (Num0 == 0) {Result = 0; PORTC = bin2bcd(Result);}
                    else {
                        Result = Num1 / Num0; PORTC = bin2bcd(Result);
                        }
                }
                else if (Operand == '*') {
                    Result = Num1 * Num0 ; PORTC = bin2bcd(Result);
                }
                State = 0; Num0 = 0; Num1 = Result;
            }
            break;
        }
    }
}