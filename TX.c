// Working on Hardware
/*
#include<p18f4580.h>
#define led PORTAbits.RA5

void delay(int a);

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<123; j++);
}
void main(){
	char i;
	TRISAbits.RA5=0;	// o/p
	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
//	SPBRG=0x19;		// 9600 B.R & 4Mhz
	SPBRG=129;		// 9600 & 20Mhz
//  SPBRG=9;		// 115200 &20Mhz

	
	while(1){
	TXREG='B';
	while(PIR1bits.TXIF==0);
	PIR1bits.TXIF=0;	
	delay(1000);
	}
}
*/
//Array through string pass
// Working on Hardware
#include<p18f4580.h>
#define led PORTAbits.RA5

void delay(int a);

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<123; j++);
}
void main(){
	char i;
	char st[]="Micro";
	TRISAbits.RA5=0;	// o/p
	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
//	SPBRG=0x19;		// 9600 B.R & 4Mhz
	SPBRG=129;		// 9600 & 20Mhz
//  SPBRG=9;		// 115200 &20Mhz

	
	while(1){
	for(i=0; st[i]!='\0'; i++){
	TXREG=st[i];
	delay(1000);
	while(PIR1bits.TXIF==0);
	PIR1bits.TXIF=0;	
	}

	}
}