#include<p18f4580.h>
#define led PORTCbits.RC0

int cnt=0;
void main()
{
TRISCbits.RC0=0;     // o/p
RCONbits.IPEN=0;     // IPen 0
//INTCON=0xC0;         // global and pheripheral interrupt
INTCONbits.GIE=1;
INTCONbits.PEIE=1;
PIE1bits.TMR1IE=1;   // timer 1 int 1 enable

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