#include<p18f4580.h>

void t0_delay(){
//	TMR3H=0xCF;
//	TMR3L=0x2B;			// 100ms
	TMR3H=0x6D;
	TMR3L=0x83;			// 300ms
	T3CONbits.TMR3ON=1;		// Start the timer
	while(PIR2bits.TMR3IF==0);	// waiting for interrupt flag
	PIR2bits.TMR3IF=0;	// clear the flag bit
	T3CONbits.TMR3ON=0;		// Stop the timer	
}
void main(){
	TRISC=0x00;	// led o/p
//	T3CON=0xf0;
	T3CON=0xB0;	// 16 bit,prescaler 1:8 1011 0000
	//T3CON=0xB8;	// pulse vary
	while(1){
		PORTC=0xff;	// led ON
		t0_delay();
		PORTC=0x00;	// led off
	 	t0_delay();
	}
}
