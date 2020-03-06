/*
 * hw6_8.c
 *
 * Created: 6/3/2563 9:21:17
 * Author : Chayanon Sukkhat
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void blink1sec(void){
	//blink every 1 secs if results = 0
	PORTD = 0xff;
	_delay_ms(1000);
	PORTD = 0x00;
	_delay_ms(1000);
}
void blinkRun(void){
	//blink running from left to right
}

	
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
			blink1sec();
		}
		else if(results < 0){
			blinkRun();
		}
		else{
			PORTD = results;
		}
		
    }
}

