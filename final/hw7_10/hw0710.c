/*
 * HW_0710.c
 *
 * Created: 3/8/2020 2:32:34 PM
 * Author : theethawat
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

char bin_to_7seg( uint8_t input);
unsigned int run_number(unsigned int number);
unsigned int check_for_reset(unsigned int data_value);
unsigned int check_for_add(unsigned int number);
void rander_value(unsigned int number);

int main(void)
{
	/* Replace with your application code */
	// 0 is input 1 is output
	
	//PORTC AS all Output
	DDRC = 0xFF;
	
	//PORTD 0,4,5,6,7 is Output 1,2 as Input
	DDRD = 0b11110001;
	
	unsigned int out_value = 1;
	unsigned int count_1sec = 0;
	while (1)
	{
		rander_value(out_value);
		count_1sec ++;
		if (count_1sec == 50)
		{
			count_1sec = 0;
			out_value = check_for_add(out_value);
			out_value = check_for_reset(out_value);
			out_value  = run_number(out_value);
		}
	}
}

void rander_value(unsigned int number){
	unsigned int temp;
	unsigned char out_led;
	//0b D4 D5 D6 D7
	static char port_d_output[] = {0b10000001,0b01000001,0b00100001,0b00010001};

	// last decimal
	temp = number % 10;
	PORTD  = port_d_output[0];
	out_led = bin_to_7seg(temp);
	PORTC = out_led;
	_delay_ms(5);
	
	// ten decimal
	temp = (number / 10) % 10;
	PORTD =  port_d_output[1];
	out_led = bin_to_7seg(temp);
	PORTC = out_led;
	_delay_ms(5);
	
	// Hundred Decimal
	temp = (number/100 )% 10;
	PORTD = port_d_output[2];
	out_led = bin_to_7seg(temp);
	PORTC = out_led;
	_delay_ms(5);
	
	//Thousand Decimal
	temp = (number/1000) % 10;
	PORTD = port_d_output[3];
	out_led = bin_to_7seg(temp);
	PORTC = out_led;
	_delay_ms(5);
	
}

unsigned int check_for_add(unsigned int number){
	unsigned char switch_input;
	switch_input = PIND;
	switch_input = switch_input & 0b00000100;
	switch_input = switch_input << 2;
	if (switch_input == 0)
	{
		//bounce delay
		_delay_ms(10);
		if(number < 9999){
			return number + 1;
		}
		else{
			return 0;
		}
	}
	else{
		return number;
	}
}

unsigned int check_for_reset(unsigned int data_value){
	unsigned char check_button;
	check_button = PIND;
	check_button &= 0b00000010; // Change to Switch 1
	check_button = check_button << 1;
	if(check_button == 0){
		check_button = PIND;
		check_button &= 0b00000100;
		check_button = check_button << 1;
		if(check_button == 0){
			return 0;
		}
		else{
			return data_value;
		}
	}
}

unsigned int run_number(unsigned int number){
	// Mode Up
	if(number < 10000){
		number ++;
		return number;
	}
	else{
		return 0;
	}
}

char bin_to_7seg(uint8_t input){
	static char lookuptable[] = {
		0x3F,
		0x06,
		0x5B,
		0x4F,
		0x66,
		0x6D,
		0x7D,
		0x07,
		0x7F,
		0x6F,
		0x77,
		0x7C,
		0x39,
		0x5E,
		0x79,
		0x71
	};
	return lookuptable[input];
}
