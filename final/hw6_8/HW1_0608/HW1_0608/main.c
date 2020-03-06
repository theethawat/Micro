/*
 * HW1_0608.c
 *
 * Created: 3/6/2020 10:56:26 AM
 * Author : Theethawat
 */ 

#include <avr/io.h>
#define F_CPU 1.2E6
#include <util/delay.h>

//Function Prototyping

void display_led_running();
void display_negative_value(int8_t data);
void display_positive_value(int8_t data);

int main(void)
{
	int8_t data,devider,result;
	/*Setting Port Direction
	 0x00 as Input 0xFF as output 
	 Port D as Output another as Output
	 */
	
	DDRD= 0xFF; 
    DDRC = 0x00;
	DDRB = 0x00; // Will mask later
	 
    while (1) 
    {
		
		data = PINB; // Receive Number from PINB 
		devider = PINC; // Receive Divider from PINC
		
		devider = devider & 0b00001111;// Mask get only PC0123 0b00001111
		if(devider == 0){
			display_led_running();
		}
		else{
			result = data / devider;
			if(result >= 0){
				display_negative_value(result);
			}
			else{
				display_positive_value(result);
			}
		}
    }
}

void display_led_running(){
	unsigned char run = 0x01;
	uint8_t counting;
	for(counting = 0; counting<8;counting++){
		PORTD = run;
		_delay_ms(1000);
		run = run << 1;
	}	
}

void display_negative_value(int8_t data){
	PORTD = data;
	_delay_ms(1000);
	PORTD = 0x00;
	_delay_ms(1000);
}

void display_positive_value(int8_t data){
	PORTD = data;
}
