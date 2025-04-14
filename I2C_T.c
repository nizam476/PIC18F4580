#include<P18f4580.h>

void I2C_Init(void);
char I2C_Start(char slave_write_address);
void I2C_Ready(void);
char I2C_Stop(void);
char I2C_Write(unsigned char data);
void delay(int a);

#define Bit_rate 100000	// 100khz

void main(){
	I2C_Init();
	delay(5);

  while(1){
	I2C_Ready();
	delay(5);

	if(I2C_Start(0x85))	// Assgning the address (programmer)
	{
	delay(5);	
	I2C_Write(0x42);	// random data 1
	delay(5);
	I2C_Write(0x8A);	// data 2
	delay(100);
	I2C_Write(0xFE);	// data 3
	delay(100);
	I2C_Stop();
	delay(5);
  }
 }
}

void I2C_Init(void){
	SSPSTAT=0x80;	//slew rate disabled, 100Khz
//	SSPSTAT=0x85;	// 100Khz
	SSPCON1=0x28;	//configure the pins,Master mode
	SSPCON2=0x00;
//	SSPCON2=0x40;
	SSPADD=Bit_rate;	// clk 100KHz
	PIR1bits.SSPIF=0;
}

void I2C_Ready(void){
	while(PIR2bits.BCLIF);	//wait if bit/bus collision interrupt flag is set.
	while(SSPSTATbits.BF || (SSPSTATbits.R));	// waiting for transmission
		
		// Optional 
//	while(PIR1bits.SSPIF==0); // waiting for tx 
//	PIR1bits.SSPIF=0;	//clear interrupt flag
}

char I2C_Start(char slave_write_address){

	SSPCON2bits.SEN=1;		//send the start pulse
	while(SSPCON2bits.SEN);	//wait for completion of start pulse
	PIR1bits.SSPIF=0;	
	if(!SSPSTATbits.S)	//check whether start detected last
// 	if( !1)	--> if(0)
		return 0;
	return(I2C_Write(slave_write_address));	// 0x85
}

char I2C_Write(unsigned char data){	// data =address(0x85)
	SSPBUF=data;	//write data into SSPBUF
	I2C_Ready();

	if(SSPCON2bits.ACKSTAT==1)	//Check ack bit 	if(0)
		return 1;			// NACK
	else
		return 0;		 	// ACK
}

char I2C_Stop(void){
	I2C_Ready();
	SSPCON2bits.PEN=1;	// Stop communication
	while(SSPCON2bits.PEN);	//wait for end of pulse
	PIR1bits.SSPIF=0;
	if(!SSPSTATbits.P);	//check whether stop is detected last
	return 0;
}

void delay(int a){
 int i,j;
	for(i=a; i<345; i++)
	for(j=0; j<12; j++);
}








































/*
void I2C_Ack(void){
	SSPCON2bits.ACKDT=0;	// Ack data 1; Nack=0
	SSPCON2bits.ACKEN=1;	//Enable Ack to send 
	while(SSPCON2bits.ACKEN);
}

void I2C_Nack(){
	SSPCON2bits.ACKDT=1;	// Ack data 1; Nack=0
	SSPCON2bits.ACKEN=1;	//Enable Ack to send 
	while(SSPCON2bits.ACKEN);//waiting for ack recieved 
}
*/