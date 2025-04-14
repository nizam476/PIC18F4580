#include <p18f4580.h>
#define CS PORTAbits.RA5

void SPI_write(char data);
void delay(unsigned int nMilliseconds);
void SPI_init();

void delay(unsigned int nMilliseconds)
{
#define CYCLES_PER_MS 100 /* Number of decrement-and-test cycles. */
unsigned long nCycles = nMilliseconds * CYCLES_PER_MS;
while (nCycles--);
}

void SPI_init()
{
// this setting selects master mode with frequency fosc/4
SSPCON1bits.SSPM0 = 0;
SSPCON1bits.SSPM1 = 0;
SSPCON1bits.SSPM2 = 0;
SSPCON1bits.SSPM3 = 0;

SSPCON1bits.SSPEN = 1;// Enable SPI Port
// Configure The Clock Polarity & Phase
SSPCON1bits.CKP = 0;
SSPSTATbits.CKE = 0;
//  Slew rate control enabled for High Speed mode
SSPSTATbits.SMP = 0;

// Set SPI pins as digital I/O
TRISCbits.RC5 = 0; // SDO -> Output
TRISCbits.RC4 = 1; // SDI -> Input
TRISCbits.RC3 = 0; // SCK -> Output
TRISAbits.RA5 = 0; // SS -> O/p

TRISBbits.RB0=1;	// GPIO input

//Uncommnent this line, if you want to send send over interrupt
// PIE1bits.SSPIE=1; INTCONbits.PEIE=1; INTCONbits.GIE=1;
}
//------------------------------------------------------------------------------
void SPI_write(char data)
{
	CS=0;
SSPBUF = data;
//while(SSPSTATbits.BF == 0);	// option we can use this BF bit also
	while(PIR1bits.SSPIF==0);
	PIR1bits.SSPIF=0;
	CS=1;
}
//-----------------------------------------------------------------------------
void main(void) 
{
	SPI_init();
	ADCON1=0x0f;
	TRISB=0x0f;
while(1)
{ 
	if(PORTBbits.RB0==0){ 
		SPI_write(0x01);    // if switch pressed, send 0x01
	}	
	else {

		SPI_write(0x02);    // if switch is pressed, send 0x02

	}
}
//return;
}







/*
// interuppt not working 
#pragma code SPI_Master_Interrupt=0x08
#pragma interrupt SPI_Master_Interrupt

void SPI_Master_Interrupt(){
	if(PORTBbits.RB0==0) 
	SPI_write(0x01);    // if switch pressed, send 0x01
	else 
	SPI_write(0x02);    // if switch is pressed, send 0x02
}
*/