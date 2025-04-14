#include <p18f4580.h>

void MSdelay(unsigned int);

void main()
{
    unsigned int duty_cycle;  
   
    TRISCbits.RC2=0;  	 /* Set CCP1 pin as output for PWM out */
    PR2=199;             /* load period value in PR2 register */ 
    CCPR1L=1;            /* load duty cycle */
    T2CON=0;             /* no pre-scalar,timer2 is off */
    CCP1CON=0x0C;        /* set PWM mode and no decimal value for PWM */
    TMR2=0;
    T2CONbits.TMR2ON=1;  /* Turn ON Timer2 */

    while(1)
    {
     for(duty_cycle=1;duty_cycle<199;duty_cycle++){
          CCPR1L = duty_cycle;   /* load duty cycle */
            MSdelay(20);
     }
     MSdelay(1000);
        
      for(duty_cycle=199;duty_cycle>1;duty_cycle--){
        CCPR1L = duty_cycle;   /* load duty cycle */
        MSdelay(20);
      }  
       MSdelay(1000);
   	} 
}

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
        for(j=0;j<165;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
}