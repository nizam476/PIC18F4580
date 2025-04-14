#include <p18f4580.h>
//#include "SPI_7Seg.h"

#define SCK PORTCbits.RC3
#define SDI PORTCbits.RC4
#define SDO PORTCbits.RC5
#define SS PORTAbits.RA5

#define WREN 0x06 //Write enable
#define WRDI 0x04 //Write Disable
#define WRITE 0x02
#define READ 0x03
#define RDSR 0x05 //Read Status Register

char EEPROM_status();
void delay(int a);
char EEPROM_wrEnable();
char EEPROM_busy();  
char EEPROM_read(int address);
void EEPROM_write(int address,char data);
char SPI_Read(char read);
void SPI_init();
void SPI_write(char data);

char data[16]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x83,0xC6,0xA1,0x86,0x8E};
/* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
int address[16] = {0x0103,0x0B31,0x1032,0x0C23,0x6004,0xC0BF,0x10C6,0x0317,0x0AF8,0x0A19,0x102A,0x0CCB,0x1388,0x612D,0x501E,0x42AF};
/* Addresses are 16 bit(hence int data type) wide <ie 4 nibbles>(According to Datasheet info). NB: Chosen at Random */


void SPI_init(){
	ADCON1=0x0f;
	TRISC=0x10;	// SDO=0, SDI=1, SCK=0;
	TRISAbits.RA5=0;
/*
	TRISCbits.RC5=0;	//SDO=0
	TRISCbits.RC4=;		//SDI=1
	TRISCbits.RC3=;		//SCK=0
*/
	SSPSTAT=0x80;	// SMP=1 Input data sampled at end of data output time. 
	SSPCON1=0x30; //SSPEN=1:Enable Serial Port. CKP = 1: Clock Polarity Select bit: Idle state for clock is a high level
}

void SPI_write(char data){
	SSPBUF=data;
	while(SSPSTATbits.BF==0);
	
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	
}

char SPI_Read(char read){
	read=SSPBUF;
	while(SSPSTATbits.BF=0);
	
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	
	return SSPBUF;
}

int i;

void main(void) 
{
	SPI_init();
	TRISD = 0;
	PORTD = data[0];
	
	SS=0;
	for(i = 0 ; i < 16 ; i++ )
		EEPROM_write(address[i],data[i]);
	SS=1;

while(1)
{
	SS=0;
	for(i = 0 ; i < 16 ; i++ )
	{
		PORTD = EEPROM_read(address[i]); //Pass Address and Return value at that very address tp PORTD
		delay(1000);
	}
	SS=1;
}
return;
}

void EEPROM_write(int address,char data)
{
	while( EEPROM_busy() == 1 );

	//Set write enable latch
SS = 0;
SPI_write(WREN);
SS = 1; //Latch-Enabled. use isWriteEn() if you want to verify

//Start Write sequence(only occurs when/if Write latch is Enanled)
SS = 0;
SPI_write(WRITE);
SPI_write(address>>8);
SPI_write(address);
SPI_write(data);
SS = 1;
}
//------------------------------------------------------------------------------
char EEPROM_read(int address)
{
char data;
while( EEPROM_busy() == 1 ); //Wait for previous Write/Read operations to finish

SS = 0;
SPI_write(READ);
SPI_write(address>>8); //Upper Byte
SPI_write(address); //Lower Byte
data = SPI_Read(0);
SS = 1;

return data;
}
//------------------------------Used as a flag----------------------------------
char EEPROM_status()
{
char status;
SS = 0;
SPI_write(RDSR); //Intsruction: Read Status register of the EEPROM
status = SPI_Read(0) ; //Send a Dummy parameter to read. Thus ANY int number is valid
SS = 1;

return status;
}
//------------------------------------------------------------------------------
char EEPROM_busy()
{
char busy;
 busy = EEPROM_status();

return (busy & 0x01); //LSB is Write-In-Process (WIP) bit. When Set, a write is in progress, when Clear, no write is in progress
}
//------------------------------------------------------------------------------
char EEPROM_wrEnable()
{
char isWrite = EEPROM_status();

return (isWrite & 0x02); //Bit 2 is the Write Enable Latch (WEL) bit and indicates the status of the write enable latch
}

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<123; j++);
}