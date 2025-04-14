#include<p18f4580.h>
#define led PORTDbits.RD0

void t0_delay(){
	TMR2=0x00;
	PR2=0x9C;	// 5ms
	T2CONbits.TMR2ON=1;// start timer
	while(PIR1bits.TMR2IF==0); //waiting for overflow
	PIR1bits.TMR2IF=0;	// flag clear 
 	T2CONbits.TMR2ON=0;// stop timer
}
void main(){
	TRISDbits.RD0=0; // o/p pin
	T2CON=0x0A;	//pre-scaler 1:16, postscaler 1:2
	while(1){
	led=~led;		// Toggle the LED
//	1	= ~0
//   0  = ~1
	t0_delay();
	}
}
/*
H.W 
WAP generate the 1sec delay & desired value
is 100ms using timer 0/1
hint : cnt, loOP
*/

100ms x10 = 1000ms 