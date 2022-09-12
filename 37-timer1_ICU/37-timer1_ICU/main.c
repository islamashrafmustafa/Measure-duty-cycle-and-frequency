/*
 * 37-timer1_ICU.c
 *
 * Created: 8/29/2022 5:48:59 AM
 * Author : islam ashraf
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "timer.h"


int main(void)
{
  unsigned short a,b,c,high,period,duty_cycle,frequency;
  LCD_vInit();
  TCCR1A=0;
  TIFR=(1<<ICF1); // Clear the ICF1
  TCCR1B=0xc1; // rising edge ,no prescalar ,noise canceler
  while((TIFR&(1<<ICF1))==0);
  a=ICR1; // take the value of capture register
  TIFR=(1<<ICF1); // Clear the ICF1
  TCCR1B=0x81;
  while((TIFR&(1<<ICF1))==0);
  b=ICR1;
  TIFR=(1<<ICF1); // Clear the ICF1
  TCCR1B=0xc1; // rising edge ,no prescalar ,noise canceler
  while((TIFR&(1<<ICF1))==0);
  c=ICR1; // take the value of capture register
  TIFR=(1<<ICF1); // Clear the ICF1
  TCCR1B=0;
  if ((a<b)&&(b<c))
  {
	  high=b-a;
	  period=c-a;
	  duty_cycle=((float)high/period)*100;
	  frequency=F_CPU/(period);
	  LCD_vSend_string("duty=");
	  LCD_vSend_char(duty_cycle/10+48);
	  LCD_vSend_char(duty_cycle%10+48);
	  LCD_vSend_char('%');
	  LCD_movecursor(2,1);
	  LCD_vSend_string("freq=");
	  LCD_vSend_char(frequency/1000+48);
	  LCD_vSend_char(((frequency/100)%10)+48);
	  LCD_vSend_char(((frequency/10)%10)+48);
	  LCD_vSend_char((frequency%10)+48);
	  LCD_vSend_string("HZ");
  }
  else 
  {
	  LCD_clearscreen();
	  LCD_vSend_string("out of range");
  }
    while (1) 
    {
    }
}

