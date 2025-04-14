
#include<p18f4580.h>
#define led PORTCbits.RC3

int cnt=0;

void main(){
ADCON1=0x0F;
TRISCbits.RC3=0;		// make o/p pins
RCONbits.IPEN=0;	// disable the priority
//INTCON=0x90;	// global Int enable, INT0 int enable,PEIE=0

INTCONbits.GIE=1;	// global Int enable
INTCONbits.INT0IE=1;//INT0 int enable
INTCONbits.PEIE=1;
PIE1bits.TMR1IE=1;   // timer 1 int 1 enable

INTCON2bits.INTEDG0=1;	// falling edge
led=0;					// led off


T1CON=0xB1;
TMR1H=0xE7;          
TMR1L=0x95;          // 50 ms      

while(1){
	if(cnt==10){	// 0<=10
	led=~led;			// 500
	cnt=0;
	}
  }
}


//#pragma code func_name=priority 
//#pragma interrupt func_name

#pragma code Ext0_ISR=0x08	// Highest priority 
#pragma interrupt Ext0_ISR	// assign the interrupt 
	
void Ext0_ISR()
{
	if(INTCONbits.INT0IF==1){	// overlow occurred
	led=~led;
	}
INTCONbits.INT0IF=0;	// clear flag bits
}

//--------------

/*
#pragma code Tim1_ISR=0x08
#pragma interrupt Tim1_ISR

void Tim1_ISR()
{
TMR1H=0xE7;          //50ms
TMR1L=0x95;

while(PIR1bits.TMR1IF==0);
//led=~led;
	cnt++;	// 1,2.....10, 11
PIR1bits.TMR1IF=0;
}
*/