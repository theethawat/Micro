#include <avr/io.h>
int main(void)
{
    uint8_t d,c,b;
    DDRD = 0XF0;
    DDRC = 0XF0;
    DDRB = OXFF;
    while(1)
    {
        d = PIND;
        c = PINC;
        d &= 0X0F;
        c &= 0x0F;
        b = d * c;
        PORTB = b;
    }
}

