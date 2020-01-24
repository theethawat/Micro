;unsigned char a=20, b=32, c= 70, d = 3,e ;
;c =  (a+b)- (c-d);
;e = a * 2 ; 
;d = (c+b)-e;

.include "m328pdef.inc"
.def TMP = R14
.def A = R15
.def B = R16
.def C = R17
.def D = R18
.def E = R19
.cseg
.org 0x0000

;--load value into variables
ldi A,20
ldi B,32
ldi C,70
ldi D,3

;--math operate
mov E,A
add E,E ;==> e = a*2 already
mov TMP,A
add TMP,B ;tmp = a + b
mov A,C ; a = c
sub A,D
mov C,TMP
sub C,A
clr TMP
mov TMP,C ;c=(a+b)-(c-d) previously
mov D,TMP
sub TMP,E