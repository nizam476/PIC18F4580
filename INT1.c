#include<p18f4580.h>
#define led PORTCbits.RC3

void main(){
ADCON1=0x0F;
TRISCbits.RC3=0;		// make o/p pins
RCONbits.IPEN=0;	// disable the priority
//INTCON=0x90;	// global Int enable, INT0 int enable,PEIE=0
INTCONbits.GIE=1;	// global Int enable
INTCON3bits.INT1IE=1;	//INT1 int enable

INTCON2bits.INTEDG1=1;	// falling edge

led=0;				// led off
	while(1);
}

//#pragma code func_name=priority 
//#pragma interrupt func_name

#pragma code Ext0_ISR=0x08	// Highest priority 
#pragma interrupt Ext0_ISR	// assign the interrupt 	
void Ext0_ISR()
{
	if(INTCON3bits.INT1IF==1){	// overlow occurred
	led=~led;
	}
INTCON3bits.INT1IF=0;	// clear flag bits
}