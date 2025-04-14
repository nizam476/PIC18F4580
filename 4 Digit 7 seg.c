/*
#include<p18f4580.h>
#define Dir_S1 TRISDbits.RD0
#define Dir_S2 TRISDbits.RD1
#define Dir_S3 TRISDbits.RD2
#define Dir_S4 TRISDbits.RD3

#define S1	PORTCbits.RD0
#define S2	PORTCbits.RD1
#define S3	PORTCbits.RD2
#define S4	PORTCbits.RD3

void delay(int a);

void main(){
int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
int i,a,b,c,d, cnt=0;

 TRISC=0x00;	// make all pins as o/p
 Dir_S1=0;		// configure the pin as o/p
 Dir_S2=0;
 Dir_S3=0;
 Dir_S4=0;
	
	S1=1;
	S2=1;	
	S3=1;
	S4=1;
	while(1){
		
	a = cnt/1000;
	b = (cnt/100)%10;
	c = (cnt/10)%10;
	d = (cnt%10);
	 
	 PORTC = arr[a];
	 S4=1;
	 delay(100);
	 S4=0;

	 PORTC = arr[b];
	 S3=1;
	 delay(100);
	 S3=0;

	 PORTC = arr[c];
	 S2=1;
	 delay(100);
	 S2=0;

	 PORTC = arr[d];
	 S1=1;
	 delay(100);
	 S1=0;

	if(cnt>=10000){
		cnt=0;
	
	}
 	cnt++;

	}
}
*/

#include<p18f4580.h>
#define Dir_S1 TRISDbits.RD0
#define Dir_S2 TRISDbits.RD1
#define Dir_S3 TRISDbits.RD2
#define Dir_S4 TRISDbits.RD3

#define S1	PORTDbits.RD0
#define S2	PORTDbits.RD1
#define S3	PORTDbits.RD2
#define S4	PORTDbits.RD3

void delay(int a);

void main(){
int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
int i,a,b,c,d, cnt=0;

 TRISC=0x00;	// make all pins as o/p
 Dir_S1=0;		// configure the pin as o/p
 Dir_S2=0;
 Dir_S3=0;
 Dir_S4=0;
	
	S1=1;
	S2=1;	
	S3=1;
	S4=1;
	while(1)
	{
	for(i=0; i<=9999; i++)
	{		
//   4th Digit
		d = (i%10);					// 1023%10 = 3
		S4=0; S3=1; S2=1; S1=1;
		PORTC= arr[d];
		delay(100);	

//   3rd Digit
		c = (i/10)%10;			// 1023/10 = (102 %10) = 2
		S4=1; S3=0; S2=1; S1=1;
		PORTC= arr[c];
		delay(50);	

// 2nd Digit
		b = (i/100)%10;				// 1023/100 = (10%10) = 0
		S4=1; S3=1; S2=0; S1=1;
		PORTC= arr[b];
		delay(50);	

// 1st Digit
		a = i/1000;			// 1023 /1000 = 1
		S4=1; S3=1; S2=1; S1=0;
		PORTC= arr[a];
		delay(50);
	 }

	}
}

/*
#include<p18f4580.h>
#define Dir_S1 TRISDbits.RD0
#define Dir_S2 TRISDbits.RD1
#define Dir_S3 TRISDbits.RD2
#define Dir_S4 TRISDbits.RD3

#define S4	PORTDbits.RD0
#define S3	PORTDbits.RD1
#define S2	PORTDbits.RD2
#define S1	PORTDbits.RD3

void delay(int a);

void main(){
int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
int i,j,a,b,c,d, cnt=0;

 TRISC=0x00;	// make all pins as o/p
 Dir_S1=0;		// configure the pin as o/p
 Dir_S2=0;
 Dir_S3=0;
 Dir_S4=0;
	
	S1=1;
	S2=1;	
	S3=1;
	S4=1;
	while(1)
	{
	for(i=0; i<=9999; i++)
	{
			a = i/1000;   		// holds 1000's digit
           b = ((i/100)%10);   	// holds 100's digit
           c = ((i/10)%10); 	 // holds 10th digit
           d = (i%10);  		// holds unit digit value  
  
for (j = 0; j< 10; j++){
          
	PORTC=arr[a]; // send 1000's place data to fourth digit
	PORTDbits.RD0=0;   //  turn on forth display unit
	delay(100);

	PORTDbits.RD0=1;   //  turn off forth display unit
	PORTC=arr[b];  // send 100's place data to 3rd digit
	PORTDbits.RD1=0;    //  turn on 3rd display unit
	delay(100);

	PORTDbits.RD1=1;  //  turn off 3rd display unit
	PORTC=arr[c];  // send 10th place data to 2nd digit
	PORTDbits.RD2 = 0;  //  turn on 2nd display unit
	delay(100);

	PORTDbits.RD2 = 1;   //  turn off 2nd display unit
	PORTC=arr[d];  // send unit place data to 1st digit
	PORTDbits.RD3 = 0;  //  turn on 1st display unit
	delay(100);
	PORTDbits.RD3 = 1;  //  turn off 1st display unit
	}
  } 
 }
}
*/
void delay(int a)
{	int i,j;
 for(i=0; i<a; i++)
 for(j=0; j<i; j++);
}