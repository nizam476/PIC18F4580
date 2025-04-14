#include<p18f4580.h>

#define led PORTDbits.RD0


//void print(const rom unsigned char *msg);
//void tx(unsigned char value);

void main(){
	char read[10];
	char msg[]="nizam";
	char new[]="\r\n";
	char msg1[]="patel";
	char *new_line=&new;	

	int i,cnt=0;
	TRISD=0x00;
//	uart_init();

	TRISC=0x80;	// tx=0, rx=1
	TXSTA=0x24;	// 8 bit, Transmit enable, Asyn mode, High Speed 
	RCSTA=0x90;	// configure rx/tx pins, 8bit reception,  Enables receiver
	SPBRG=0x19;		// 9600 B.R
//	SPBRG=129;


	while(1){
	for(i=0; i<6; i++){
		read[i]=RCREG;
		while(PIR1bits.RCIF==0);// waiting for recieving data
		PIR1bits.RCIF=0;
	}	

	read[i]='\0';
	
	for(i=0; i<6; i++){
		TXREG=read[i];
		while(PIR1bits.TXIF==0);// waiting for recieving data
		PIR1bits.TXIF=0;
	}	
	while(*new_line){
	TXREG=*new_line;
	new_line++;
	}
// Sending data to LCD
	i=0; 
	while(read[i]!='\0' == msg[i]!='\0');
		led=1;
	while(read[i]!='\0' == msg1[i]!='\0');
		led=0;
/*
	i=0; 
	while(msg[i]!='\0' && read[i]!='\0'){
		// l !='\0'			l!='\0'
			cnt++;	// 1
		if(cnt==6){
			led=1;
		}
	i++;
	//str++;
	}
*/
  }
}
