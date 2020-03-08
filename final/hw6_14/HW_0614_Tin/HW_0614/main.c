/*
 * HW_0614.c
 *
 * Created: 3/8/2020 3:06:03 PM
 * Author : theethawat
 */ 

#include <avr/io.h>
#define F_CPU  16000000UL
#include <util/delay.h>

void display_number(uint8_t number);
char disp_7seg(uint8_t input);
uint8_t run_number(unsigned char direction,uint8_t number,uint8_t limit);
uint8_t read_dipswitch(char select_place);
uint8_t merge_limit(uint8_t edgeten,uint8_t edgeone);
unsigned char get_direction();

int main(void)
{
	/* Replace with your application code */
	// Port A and B as Input Port C and D as Output
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0xFF;
	uint8_t edge_ten,edge_one,limit,number;
	number = 0;
	unsigned char direction = 1;
	while (1)
	{
		edge_ten = read_dipswitch(1);
		edge_one = read_dipswitch(2);
		limit = merge_limit(edge_ten,edge_one);
		direction = get_direction();
		number = run_number(direction,number,limit);
		display_number(number);
	}
}


void display_number(uint8_t number){
	uint8_t display;
	char output;
	display = number % 10; // ones
	output = disp_7seg(display);
	PORTD = output;
	display = (number / 10) % 10; //tens
	output = disp_7seg(display);
	PORTC = output;
	_delay_ms(1000);
}

char disp_7seg(uint8_t input){
	// Common Anode 7 Segment LED
	static char lookuptable[] = {
		0x40,
		0x79,
		0x24,
		0x30,
		0x19,
		0x12,
		0x02,
		0x78,
		0x00,
		0x10
	};
	return lookuptable[input];
}

uint8_t run_number(unsigned char direction,uint8_t number,uint8_t limit){
	if (direction == 0)	//down
	{
		if (number > 0 )
		{
			number --;
		}
		else{
			number = limit;
		}
	}
	else if (direction == 1) // up
	{
		if (number < limit)
		{
			number ++;
		}
		else{
			number = 0;
		}
	}
	return number;
}

uint8_t read_dipswitch(char select_place){
	uint8_t temp;
	if (select_place == 1)
	{
		temp = PINA;
	}
	else if(select_place ==2){
		temp = PINB;
	}
	temp &= 0b00011111;
	if(temp > 9){
		temp = 9 ; // 0b00001001
	}
	return temp;
}

uint8_t merge_limit(uint8_t edgeten,uint8_t edgeone){
	uint8_t temp;
	temp = edgeten * 10;
	temp = temp + edgeone;
	return temp;
}

unsigned char get_direction(){
	// 1 as up, 0 as down
	uint8_t temp;
	temp = PINB;
	temp &= 0b10000000;
	temp = temp >> 7;
	return temp;
}


