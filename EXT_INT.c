#include<p18f4580.h>
// External interrupt 0
#define led PORTBbits.RB7

void main(){
	ADCON1=0x0f;	// make digital i/p & o/p
	TRISBbits.RB0=1;	// i/p
	TRISBbits.RB7=0;	// o/p

	INTCON=0x90;	// global, Ext 0 enable
/* optional
	INTCONbits.GIE=1;	// global Enable 
	INTCONbits.INT0IE=1;// Ext 0 enable
*/	
	INTCON2bits.INTEDG0=0;	// faliing edge
	while(1);
}
/*
	Syntax
#pragma code funct_name=priority(high/low)
#pragma interrupt funct_name
*/
#pragma code Ext_Int0_ISR=0x08 // Highest priority to function
#pragma interrupt Ext_Int0_ISR	//Accessing the Interrupt to Function 

void Ext_Int0_ISR()
{
//	while(INTCONbits.INT0IF==0);// Interrupt not occured
	if(INTCONbits.INT0IF==1)// overflow occured
	{	
	led=~led;
	}
	INTCONbits.INT0IF=0;	// clear flag bit
}