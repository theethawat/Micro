/*
 * hw6_8.c
 *
 * Created: 6/3/2563 9:21:17
 * Author : Chayanon Sukkhat
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xff; //port D as output
	DDRB = 0x00; //port B(dipsw8) as input
	DDRC = 0x00; //port C(dipsw4) as input

	char inputFromPinB, inputFromPinC, results;
	    
    while (1) 
    {
		inputFromPinB = PINB; //use all of 8 inputs
		inputFromPinC = PINC & 0x0f; //mask upper 4 bits
		results = inputFromPinB / inputFromPinC;
		if(results == 0)
		{
			//blink every 1 secs if results = 0
			PORTD = 0xff;
			_delay_ms(1000);
				
		}
		
    }
}

