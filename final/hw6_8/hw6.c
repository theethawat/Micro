#include<avr/io.h>
int main(void){
    uint8_t d,c,b;
    DDRD = 0XF0;
    DDRC = 0XF0;
    DDRB = 0XFF;
    while(1){
        d = PIND;
        c = PINC;
        d &= 0x0F;
        C &= 0x0F;
        b = d*c;
        PORTB = b;

    }
}
