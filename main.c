//program to control position of a 2DC motor and one optical servo motor by potentiometers
/********************************************************************************
date:-15th Dec 2010
Target system-AVR devlopment board s/n-107010 
microcontroller: ATmega-8535
clock: 16mhz

compiler win avr

======================= PORTS DETAILS =======================

##################### MOTOR DRIVERS USED ###################

M0-PortB0 & M1-PortB1 --- WRIST Motor/Yellow Motor (120RPM) 

M4-PortD4 & M5-PortD5 --- CLAW Motor/Yellow Motor (120RPM)

M6-PortD6 & M7-PortD7 --- BASE Motor/White motor (60RPM)

###################### INTERRUPTS USED #####################

INT2 --- PortB2 --- for WRIST Motor (Pin No. 3)

#################### POTENTIOMETERS USED ###################

POT0 --- PortA0 --- for BASE Motor (Pin No. 40)

POT1 --- PortA1 --- for CLAW Motor (Pin No. 39)

POT2 --- PortA2 --- for WRIST Motor (Pin No. 38)

*********************************************************************************/
#include<avr/io.h>
#include<avr/interrupt.h>
#include"delay.h"
#include"adc.h"
#include"optservo.h"

int main(void)
{
 unsigned char digital0,digital1,predigital0,predigital1;
 unsigned int digital2;
 delayms(1000);
 
 adc_init();
  
 digital2=getdata(2);

 optservo_init((digital2*4)+3);
 
 DDRD=0xF0;
  
 while(1)
 {
  digital0=getdata(0);		//read ADC from channel 0 for base motor
  digital1=getdata(1);		//read ADC from channel 1 for claw motor
  digital2=getdata(2);		//read ADC from channel 2 for optical servo (wrist) motor
  
  move((digital2*4)+3);	//Wrist Motor
   
  PORTD=0x00;
  
  if(digital0>predigital0) 	//Base Motor
  {
   PORTD &=0x3F;
   PORTD |=0x40;
  }
  if(digital0<predigital0) 
  {
   PORTD &=0x3F;
   PORTD |=0x80;
  }
  
  if(digital1>predigital1) 	//Claw Motor
  {
   PORTD &=0xCF;
   PORTD |=0x10;
  }
  if(digital1<predigital1) 
  {
   PORTD &=0xCF;
   PORTD |=0x20;
  }

	delayms(0.2);
  
  predigital0=digital0;
  predigital1=digital1;
 }
}