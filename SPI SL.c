#include<p18f4580.h>
#define LED PORTBbits.RB1

void SPI_init();

char data;

void delay(unsigned int nMilliseconds)
{
#define CYCLES_PER_MS 100 /* Number of decrement-and-test cycles. */
unsigned long nCycles = nMilliseconds * CYCLES_PER_MS;
while (nCycles--);
}

void SPI_init()
{
	/*
	   SSPSTAT =0x00; // Clock Phase =0
	   SSPCON1 =0x24	// Mode 1, Slave mode + SS Enabled
	*/
	
	// Set Spi Mode To Slave + SS Enabled 
	SSPCON1bits.SSPM0 = 0;
	SSPCON1bits.SSPM1 = 0;
	SSPCON1bits.SSPM2 = 1;
	SSPCON1bits.SSPM3 = 0;
	// Enable The Synchronous Serial Port
	SSPCON1bits.SSPEN = 1;
	// Configure The Clock Polarity & Phase (SPI Mode Num. 1)
	SSPCON1bits.CKP = 0;
	SSPSTATbits.CKE = 0;
	// Clear The SMP Bit
	SSPSTATbits.SMP = 0;
	
	// Configure The IO Pins For SPI Master Mode
	TRISCbits.RC5 = 0; // SDO -> Output
	TRISCbits.RC4 = 1; // SDI -> Input
	TRISCbits.RC3 = 1; // SCK -> Intput
	TRISAbits.RA5 = 1; // SS -> Input
	
	// Enable Interrupts. Comment Them To Disable interrupts(NOT Recommended)
	PIE1bits.SSPIE = 1;		// Enable SPI Interrupt
	INTCONbits.PEIE = 1;	// Enable Peripheral Interrupt
	INTCONbits.GIE = 1;		// Enable Global Interrupt 
}

void main(void) 
{
	SPI_init();
	ADCON1=0x0f;
	TRISB = 0x00;

while(1){
/*
	while(PIR1bits.SSPIF==0);
	 data = SSPBUF;
PIR1bits.SSPIF=0;
*/
	if (data==0x01)     
	{
		PORTBbits.RB1=1;       //if received data = 0x01, turn on LED
	}
	if (data==0x02)
	{
		PORTBbits.RB1=0;  //if received data = 0x02, turn off LED
	}
 }
}

#pragma code SPI_interrupt=0x08
#pragma interrupt SPI_interrupt
 
void SPI_interrupt()  {
//	if(PIR1bits.SSPIF==1){  // check if interrupt occurs due to SPI module
	
	data = SSPBUF; // copy data from receive buffer into a global variable data
	PIR1bits.SSPIF = 0; // reset flag interrupt for SPI module
//	}
}