/*
 * Startup.c
 *
 * Created: 9/13/2014 1:46:24 PM
 *  Author: baghi
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>


void Startup(void)
{
	DDRB=0b00000011;
	PORTC=0b001110;
	DDRC=0b000000;
	DDRD=0b10010000;
	
	//----TMR0
	// 10Mhz/(256*1024)=38.14Hz     =     26.2ms
	TCCR0|=0b101;
	TIMSK|=0b1;
	
	//INT0 & INT1
	MCUCR|=0b1111;
	GICR|=0b11000000;
	
	//Global interrupt enable
	sei();
	
	
}