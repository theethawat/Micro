.include "m328Pdef.inc"

.equ all_pin_out = 0xff
.equ all_pin_in = 0x00
.def a = r16
.def tmp = r17

;=====  code segment ==========
.cseg
.org 0x0000
    ldi a, all_pin_out
    out ddrb, a ;port b as output

    ldi a,all_pin_in
    out ddrc, a ; port c as input

    ldi tmp, 0x00 ;tmp <= 0

main:   
    ;------- read 4 switchs
    in a, pinc   ; 4 switches are connected to bit 0-3
    andi a,0x0f  ; upper 4 bits are filtered out 
    
    ;------- look table
    ldi zl, low(tb_7segment*2) ; load z register low
    ldi zh, high(tb_7segment*2) ; load z register high

    add zl, a ; z <= z + a
    adc zl, tmp ; load z register high
    lpm ; r0 <== [z]
    
    com r0 ; complement r0
    out portb, r0
    rjmp main


;===== Table for 7seg disp
tb_7segment: 
    .db 0b00111111, 0b00000110 ; 0 and 1
    .db 0b01011011, 0b01001111 ; 2 and 3
    .db 0b01100110, 0b01101101 ; 4 and 5
    .db 0b01111101, 0b00000111 ; 6 and 7
    .db 0b01111111, 0b01101111 ; 8 and 9
    .db 0b01110111, 0b01111100 ; a and b
    .db 0b00111001, 0b01011110 ; c and d
    .db 0b01111001, 0b01110001 ; e and f

;======= data segment
.desg

;==== eeprom segment
.eseg
