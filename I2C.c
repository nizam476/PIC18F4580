/*
#include<p18f4580.h>
void I2C_init(void);
char I2C_start(char slave_write_address);
void I2C_ready(void);
char I2C_write(char data);
char I2C_stop(void);
char I2C_read(char flag);
void I2C_ack(void);
void I2C_nack(void);
void delay(int a);
#define Bit_rate 100000  // 100Khz speed

void main(){
	I2C_init();
	delay(5);
	I2C_ready();
	delay(5);
	I2C_start(0x85);	// address
	delay(5);
	I2C_stop();

while(1){
	I2C_init();
	delay(5);
	I2C_ready();
	delay(5);
	I2C_start(0x85);	// address
	delay(5);
	I2C_write(0x32);	// data tx
	delay(5);
//	I2C_write(0x56);	// 2nd data
	I2C_stop();
	}
}

void I2C_init(void){
	SSPSTAT=0x80; // slew rate disabled std mode speed
	SSPCON1=0x28; //, other bits are cleared
	
	SSPCON2=0;
	SSPADD=Bit_rate;  //clock 100Khz speed 
//	PIE1bits.SSPIE=1; //enable SSPIF interrupt
//	PIR1bits.SSPIF=0;
}

char I2C_start(char slave_write_address){
	SSPCON2bits.SEN=1; //send start pulse
	while(SSPCON2bits.SEN); //wait for completion of start pulse
	PIR1bits.SSPIF=0;
	if(!SSPSTATbits.S) //check weather START detected last
	return 0;    //return 0 to indicate start failed
	return (I2C_write(slave_write_address)); //write slave device address with write to communication 
}

void I2C_ready(void){
	
	while(PIR2bits.BCLIF); //wait if bit 
						//collision interrupt flag is set
// while(PIR2bits.BCLIF==1);
	while(SSPSTATbits.BF || (SSPSTATbits.R));// waiting for tx completed
// while(BF==1 || R==1)

	PIR1bits.SSPIF=0;   //clear SSPIF interrupt flag
}

char I2C_write(char data){	// 
	
	SSPBUF=data; //write data to SSPBUF
	I2C_ready();
	if(SSPCON2bits.ACKSTAT)//check for ack bit
		return 1;
	else
		return 0;
}

char I2C_stop(void){
	I2C_ready();
	SSPCON2bits.PEN=1;   //stop communication
	while(SSPCON2bits.PEN); //wait for end of stop pulse
	PIR1bits.SSPIF=0;
	if(!SSPSTATbits.P);  //check wether STOP is detected last
	return 0;  //if not return 0 to indicate start failed
}
	// Recieve / slave mode
char I2C_read(char flag){
	int buffer=0;
	SSPCON2bits.RCEN=1;  //enable received
	
	//wait for buffer full flag which when complete byte reveived
	while(!SSPSTATbits.BF);
	buffer =SSPBUF;   //copy SSPBUF to buffer
	//send ackor negative ack after read to continue or stop reading
	if(flag==0)
	  I2C_ack();
	else
		I2C_nack();
	I2C_ready();
	return(buffer);
} 


void I2C_ack(void){
	SSPCON2bits.ACKEN=1;		//enable ACK to send 
	SSPCON2bits.ACKDT=0;  //ack data 1:NACK, 0:ACK
	while(SSPCON2bits.ACKEN);
}

void I2C_nack(void){
	SSPCON2bits.ACKDT=1;  //ack data 1:NACK, 0:ACK
	SSPCON2bits.ACKEN=1;		//enable ACK to send 
	while(SSPCON2bits.ACKEN);
}

void delay(int a){
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<i;i++);
}
*/

#include<P18f4580.h>

void I2C_Init(void);
char I2C_Start(char slave_write_address);
void I2C_Ready(void);
char I2C_Stop(void);
void I2C_Ack(void);
char I2C_Write(unsigned char data);
void I2C_Nack(void);
void delay(int a);

#define Bit_rate 100000

void main(){
//	TRISC=0X00;

	I2C_Init();
	delay(5);
	I2C_Ready();
	delay(5);
	I2C_Start(0x85);
	delay(5);
	I2C_Write(0x55);
	delay(5);
	I2C_Stop();
	delay(5);
  while(1){
	I2C_Init();
	delay(5);
	I2C_Ready();
	delay(5);
	I2C_Start(0x85);	// adress
	delay(5);	
	I2C_Write(0x45);	// data
	delay(5);
	I2C_Write(0x8A);
	I2C_Stop();
	delay(5);
 }
}

void I2C_Init(void){
	SSPSTAT=0x80;	//slew rate disabled
	SSPCON1=0x28;	//configure the pins,Master mode
	SSPCON2=0;
	SSPADD=Bit_rate;	// clk 100KHz
	PIE1bits.SSPIE=1;	//Enable SSPIF interrupt
	PIR1bits.SSPIF=0;
}
void I2C_Ready(void){
	while(PIR2bits.BCLIF);	//wait if bit collision interrupt flag is set.
	while(SSPSTATbits.BF || (SSPSTATbits.R));
	PIR1bits.SSPIF=0;	//clear interrupt flag
}

char I2C_Start(char slave_write_address){
	SSPCON2bits.SEN=1;	//send the start pulse
	while(SSPCON2bits.SEN);	//wait for completion of start pulse
	PIR1bits.SSPIF=0;	
	if(!SSPSTATbits.S)	//check whether start detected last
		return 0;
	return(I2C_Write(slave_write_address));
}

char I2C_Write(unsigned char data){
	SSPBUF=data;	//write data into SSPBUF
	I2C_Ready();
	if(SSPCON2bits.ACKSTAT)	//Check ack bit
		return 1;
	else
		return 2;
}

char I2C_Stop(void){
	I2C_Ready();
	SSPCON2bits.PEN=1;	// Stop communication
	while(SSPCON2bits.PEN);	//wait for end of pulse
	PIR1bits.SSPIF=0;
	if(!SSPSTATbits.P);	//check whether stop is detected last
	return 0;
}

char I2C_Read(char flag){
	int buffer=0;
	SSPCON2bits.RCEN=1;	// Enable receive
	while(! SSPSTATbits.BF);// wait for buffer full flag which when complete byte received
	buffer=SSPBUF;		// Copy to buffer
	if(flag==0)
		I2C_Ack();
	else
		I2C_Nack();
//I2C_ready();	// try
	return(buffer);
}

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

void delay(int a){
 int i,j;
	for(i=a; i<345; i++)
	for(j=0; j<12; j++);
}