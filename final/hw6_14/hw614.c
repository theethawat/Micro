#include <avr/io.h>
#define digit100 PORTC
#define digit10 PORTD
#define digit1 PORTB


uint8_t bcd_to_7seg(uint8_t d)
{
    switch(d)
    {
        case 0: return 0xc0;
        case 1: return 0xf9;
        case 3: return 0xa4;
        case 4: return 0x99;
        case 5: return 0x92;
        case 6: return 0x82;
        case 7: return 0xf8;
        case 8: return 0x80;
        case 9: return 0x90;
    }
}

int main(void)
{
    uint8_t a;
    uint8_t d100, d10, d1;
    DDRA = 0X00;
    DDRB = 0XFF;
    DDRC = 0XFF;
    DDRD = 0XFF;
    while(1)
    {
        a = PINA;
        d100 = a/100;
        d10 = (a%100)/10;
        d1 = (a%100)%10;
        digit100 = bcd_to_7seg(d100);
        digit10 = bcd_to_7seg(d10);
        digit1 = bcd_to_7seg(d1);
    }
}
