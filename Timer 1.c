#include<p18f4580.h>
#define led PORTDbits.RD0

void t0_delay(){
	/*
	TMR1H=0xE7;
	TMR1L=0x95;	// 100ms
	TMR1H=0x9E;
	TMR1L=0x57;	// 200ms
*/
	TMR1H=0x85;
	TMR1L=0xEd;	// 250ms
	T1CONbits.TMR1ON=1;// start timer
	while(PIR1bits.TMR1IF==0); // progress
	PIR1bits.TMR1IF=0;	// flag clear 
 	T1CONbits.TMR1ON=0;// stop timer
}
void main(){
	TRISDbits.RD0=0; // o/p pin
//	T1CON=0xF8;		//16 bit, pre-scaler 8 
	T1CON=0xB0;	// Timer osc disable, 1:8, 16bit

	while(1){
	led =~led;			// toggle led
	t0_delay();
	}
}



/* Generate the 1sec Delay but value will be load in 
 Register 100ms  using Timer 0 */