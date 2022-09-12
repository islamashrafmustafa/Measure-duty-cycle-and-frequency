/*
 * timer.c
 *
 * Created: 8/19/2022 8:38:41 AM
 *  Author: Islam Ashraf Mustafa
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_macros.h"


void timer_CTC_init_interrupt(void)
{
	// wave generation mode
	SET_BIT(TCCR0,WGM01);
	// load value in OCR0
	OCR0=80;
	// clock select
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	sei();
	// interrupt mask register
	SET_BIT(TIMSK,OCIE0);
}