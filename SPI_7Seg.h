#include<p18f4580.h>
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
	TRISC=0x10;	// SDO=0, SDI=1, SCK=0;
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
	/*
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	*/
}

char SPI_Read(char read){
	read=SSPBUF;
	while(SSPSTATbits.BF=0);
	/*
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	*/
	return SSPBUF;
}