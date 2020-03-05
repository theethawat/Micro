#include <avr/io.h>

unsigned char pow(unsigned char base, unsigned char power){
    if(power == 0){
        return 1;
    }
    unsigned char result = 1;
    for(unsigned char i = 0;i<power;i++){
        result *= base;
    }
}
unsigned char binToGray()
int main(void)
{   
    DDRD = 0xff; //port d as output
    DDRC = 0x00; //port c as sw2
    DDRB = Ox00; //port b as sw1
    unsigned char inputFromPinC;
    unsigned char inputFromPinB;
    while(1)
    {
        inputFromPinC = PINC;
        inputFromPinC &= 0x01;

        if(inputFromPinC){
            PORTD = 
        }
    }
}