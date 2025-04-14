#include<p18f4580.h>
#define led PORTDbits.RD0

void main(){
	char temp;
	TRISDbits.RD0=0;	// o/p
	TRISC=0x80;	// tx=0, rx=1

	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
	SPBRG=0x19;		// 9600 B.R

	while(1){
	while(PIR1bits.RCIF==0);// waiting for recieving data
		temp=RCREG;
	PIR1bits.RCIF=0;
		switch(temp){
		case '1':
			led=1;
		break;
		case '0':
			led=0;
		break;
		
		}

	}
}