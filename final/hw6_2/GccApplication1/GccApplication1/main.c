#include <avr/io.h>

unsigned power(unsigned base, unsigned exponent)
{
	unsigned result = 1;
	for (exponent; exponent>0; exponent--)
	{
		result = result * base;
	}
	return result;
}

unsigned char gray2bin(unsigned char x){
	return x ^ (x>>1);
}
int main(){

	DDRD = 0xFF;  // Define PORTD to be output
	DDRB = 0x00;  // Define PORTB to be input
	DDRC = 0x00;  // Define PORTC to be input

	unsigned char inputFromPinC; // variable to store 8 bit input value from PINC
	unsigned char inputFromPinB; // variable to store 8 bit input value from PINB


	while(1){

		inputFromPinC = PINC;   // Read from PINC
		inputFromPinC &= 0x01;  // Filter upper 7 bits out

		if(inputFromPinC){ // input from PINC0 is 1

			inputFromPinB = PINB; // read input from PINB
			unsigned char greyResult = gray2bin(inputFromPinB); // convert 8 bits binary into 8 bits gray code
			PORTD = greyResult; // output result 8 bits gray code
			}
			else{ 
				// input from PINC0 is 0
				inputFromPinB = PINB; // read input from PINB
				PORTD = inputFromPinB; // output result 8 bits gray code
		}
	}

}