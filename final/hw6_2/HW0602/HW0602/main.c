/*
 * HW0602.c
 *
 * Created: 3/9/2020 8:11:56 PM
 * Author : theet
 */ 

#include <avr/io.h>
unsigned char read_dip_2();
unsigned char change_to_gray(unsigned char input);

int main(void)
{
	//Port B,C0 as Input D as Output
    DDRB = 0x00;
	DDRC = 0xF0;
	DDRD = 0xFF;
	unsigned char direc,output,input;
	/* Replace with your application code */
    while (1) 
    {
		direc = read_dip_2();
		// if 0 change to gray if 1 output
		input = PINB;
		if(direc ==0){
			output = change_to_gray(input);
		}
		else if(direc ==1){
			output = input;
		}
		PORTD = output;
	}
}

unsigned char change_to_gray(unsigned char input){
	unsigned char depli_input,gray_code;
	depli_input = input>> 1;
	gray_code = input + depli_input;
	gray_code &= 0b01111111;
	input &= 0b10000000;
	gray_code = gray_code + input;
	return gray_code;
}

unsigned char read_dip_2(){
	unsigned char direc;
	direc = PINC;
	direc &= 0x01; // LSB Mask
	return direc;
}