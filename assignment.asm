.include "m328Pdef.inc"
.equ all_pin_out = 0xff
.equ all_pin_in = 0x00
.def a = r16
.def tmp = r17
.def delay_counter1 = r18
.def delay_counter2 = r19
.def delay_counter3 = r20
.def counter = r21

;=====  code segment ==========
.cseg
.org 0x0000
    ldi a, all_pin_out
    out ddrd, a ;port d as output

    ldi a,all_pin_in
    out ddrc, a ; port c as input

    ldi tmp, 0x00 ;tmp <= 0



init_counter:
	ldi counter,0x00 ;initiate counter to all 0s	
loop_count:
	in a, pinc
	andi a,0x01 ;filter out only 1 bit
	cpi a,0x00 ; check if r3 is 0
	;r3 == 0 ==> even
	;r3 == 1 ==> odd
	breq even_count

odd_count:
	mov r4, counter  ;
	andi counter, 0x01 ;check the last bit
	cpi counter,0x00 ; compare with 0
	breq change_to_odd_count ;if current counter is even, change to odd
	ldi counter, 2			; else do odd ===> +2
	add counter, r4						 
	rjmp disp_7seg

change_to_odd_count:		; chabge count by +1
	ldi counter,0x01
	add counter, r4
	rjmp delay_loop	
	 
even_count:
	mov r4, counter  ;
	andi counter, 0x01 ;check the last bit
	cpi counter,0x00 ; compare with 0
	brne change_to_even_count    ;if current counter is odd, change to even
								
	ldi counter, 0x02			; else do odd ===> +2
	add counter, r4						 
	rjmp disp_7seg
	
change_to_even_count: ; +1
	ldi counter,0x01
	add counter, r4
	rjmp disp_7seg	

disp_7seg:
	ldi zl,low(tb_7segment*2)
	ldi zh, high(tb_7segment*2)
	ldi tmp,0x00
	andi counter,0x0F
	add zl, counter
	adc zh, tmp
	lpm  ;====load to r0
	out portd,r0

	ldi delay_counter1, 0x00
	ldi delay_counter2, 0x00
	ldi delay_counter3, 0x00

delay_loop:
	cpi delay_counter1,0xff
	breq check_delay_counter2
	inc delay_counter1
	rjmp delay_loop
 
check_delay_counter2:
	cpi delay_counter2,0xff
	breq check_delay_counter3
	inc delay_counter2
	ldi delay_counter1,0x00
	rjmp delay_loop

check_delay_counter3:
	cpi delay_counter3,0x0f
	breq loop_count
	inc delay_counter3
	ldi delay_counter2,0x00
	rjmp delay_loop



;===== Table for 7seg disp
				;      6543210
tb_7segment: ;         gfedcba
    .db 0b00111111, 0b00000110 ; 0 and 1
    .db 0b01011011, 0b01001111 ; 2 and 3
    .db 0b01100110, 0b01101101 ; 4 and 5
    .db 0b01111101, 0b00000111 ; 6 and 7
    .db 0b01111111, 0b01101111 ; 8 and 9
    .db 0b01110111, 0b01111100 ; a and b
    .db 0b00111001, 0b01011110 ; c and d
    .db 0b01111001, 0b01110001 ; e and f

;======= data segment
;.desg

;==== eeprom segment
.eseg
