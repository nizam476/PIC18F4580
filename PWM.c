#include<p18f4580.h>        	

void main()
{
	TRISCbits.RC2=0;	// Make pin as Digital o/p
	CCP1CON=0x2C;     // Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>bits
	CCPR1L= 5;  		// Duty Cycle 50%
  	PR2=11;      	 //Set the PWM period by writing to the PR2 register (5Khz)	        
//	CCPR1L= 1;        //Set the duty cycle (10%)period by writing to the CCPR1L register 

	/* optional
	T2CONbits.TMR2ON=0;		//Intially stop timer
	T2CONbits.T2CKPS1=1;    // Timer2 clock prescalar select bit 1:16
	T2CONbits.T2CKPS0=0;       
	*/
	T2CON=0x02;				// timer off, prescaler 16
	T2CONbits.TMR2ON=1;      //  Timer2 ON bit 
	TMR2=0;
//	PR2=61;  
   
	while(1);       
}



/*

#include<p18f4580.h>        	

void main()
{
	TRISC=0x00;             // Set PORTC as output 
	T2CON=0X02;	// prescaler 1:16                      
	T2CONbits.TMR2ON=0;	//Intially stop timer
	CCP1CON=0x0C;         // Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>bits
	CCPR1L= 6;          
	//CCPR1L= 8;        // Set the duty cycle period by writing to the CCPR1L register 
	T2CONbits.T2CKPS1=1;    // Timer2 clock prescalar select bit
	T2CONbits.T2CKPS0=0;       
	T2CONbits.TMR2ON=1;      //  Timer2 ON bit 
	PR2=12;  
    // PR2=30;       //Set the PWM period by writing to the PR2 register
	while(1){
	TMR2=0;
	while(PIR1bits.TMR2IF==0);
	PIR1bits.TMR2IF=0;
	}       
}
*/
/*
#include<p18f4580.h>        	
void Set_DC(unsigned int dc);
void delay(int a);

void main()
{
	int i;

	TRISC=0x00;           // Set PORTC as output                       
	T2CONbits.TMR2ON=0;	//Intially stop timer
	CCP1CON=0x0C;         // Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>bits       
    PR2=0xff;       //Set the PWM period by writing to the PR2 register
	T2CONbits.TMR2ON=1;      //  Timer2 ON bit 
	TMR2=0;
 
	while(1){
	for(i=0; i<1023; i++){
		Set_DC(i);
		delay(100);
	}
    for(i=1023; i>=0; i++){
		Set_DC(i);
		delay(100);
	}
 }
}

void Set_DC(unsigned int dc){
	CCPR1L=dc>>2;
	CCP1CON= CCP1CON & 0xCF;
	CCP1CON =CCP1CON | (0x30 & (dc<<4));
}

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<123; j++);

}
*/