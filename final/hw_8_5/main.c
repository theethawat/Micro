/*
 * HW0805.c
 *
 * Created: 3/17/2020 10:43:36 AM
 * Author : theethawat 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

signed char press_key;
signed char row;

int main(void)
{
	// Port and Pin Direction Setting
	//PORT D and PORT B will be output
	DDRB = 0b00001111; // 0x0F
	DDRD = 0b11110111; //0xFF but INT1 is located on PD3, it must be input 
	
	//PORT C will be input
	DDRC = 0b11111000;
	
	//Interrupt Flag Setting EIMSK,EICRA
	// bit 1 must be 1 (active)
	EIMSK = 0x02;
	
	//falling edge and logic low interrupt
	EICRA = 0b0100; 
	
	//Interrupt Setting
	sei();
	
	// Initial Setting
	// Input will hold all port high because we want interrupt on low
	PORTC = 0x07; //0b111
	
	// Output reset with all low because we want low to toggle interrupt 
    PORTB = 0x00;
	
	// Hold high logic in Interrupt port INT0
	PORTD |= (1<<3);
	switch_green_off();
	switch_red_off();
	
	while (1) 
    {
    }
}

// Switch Control, Switch using Active Low
void switch_red_on(){
	PORTD &= 0b11011111; //PD5 Low
}

void switch_green_on(){
	PORTD &= 0b11101111;//PD4 Low
}

void switch_red_off(){
	PORTD |= 0b00100000; //Only PD5 Must High 
}

void switch_green_off(){
	PORTD |= 0b00010000; //Only PD4 Must Low
}

// Blink Setting
void blink_red(){
	switch_red_on();
	_delay_ms(500);
	switch_red_off();
	_delay_ms(500);
}

void blink_green(){
	switch_green_on();
	_delay_ms(500);
	switch_green_off();
	_delay_ms(500);
}

//Interrupt Service Routine of INT1
ISR(INT1_vect){
	
	// Initial press_key with -1 represent to key pressed
	press_key = -1; 
	
	// Initial row to 1 represent start search with row 1
	row = 1;
	
	do 
	{
		//using port B output logic to find and Port C input logic to check
		if (row == 1)
		{
			// Check For Row 1,PB3 must be 0 (We have 1,2,3 in row 1) 
			PORTB = 0b11110111;
			_delay_ms(10); //bounce check
			
			// Read Value from PINC
			switch(PINC & 0x07){
				case 0b011:
					press_key = 3; break;
				case 0b101:
					press_key = 2; break;
				case 0b110:
					press_key = 1; break;
			}
		}
		
		else if(row ==2){
			// Check For Row 2, PB 2 Must be 0
			PORTB = 0b11111011;
			_delay_ms(10); // bounce check
			
			// Read Value from PINC
			switch(PINC & 0x07){
				case 0b011:
					press_key = 6; break;
				case 0b101:
					press_key = 5; break;
				case 0b110:
					press_key = 4; break;
			}
		}
		
		else if(row ==3){
		// Check For Row 3, PB 1 Must be 0
		PORTB = 0b11111101;
		_delay_ms(10); // bounce check
		
		// Read Value from PINC
			switch(PINC & 0x07){
				case 0b011:
					press_key = 9; break;
				case 0b101:
					press_key = 8; break;
				case 0b110:
					press_key = 7; break;
			}
		}
		
		else if(row ==4){
			// Check For Row 0, PB 0 Must be 0
			PORTB = 0b11111110; 
			_delay_ms(10); // bounce check
			
			// Read Value from PINC
			switch(PINC & 0x07){
				case 0b011:
				press_key = 11; break;
				case 0b101:
				press_key = 0; break;
				case 0b110:
				press_key = 10; break;
			}
		}
		
		row ++;
	} while (row <= 4);
	
	if (press_key == 0)
	{
		for (int i=0;i<5;i++) // blink for 5 times
		{
			blink_red();
		}
	}
	else if (press_key != -1) // other button but not no click 
	{
		for(int i=0;i<press_key;i++){
			blink_green();
		}
	}
	PORTB = 0b0000; // for receive next interrupt
}