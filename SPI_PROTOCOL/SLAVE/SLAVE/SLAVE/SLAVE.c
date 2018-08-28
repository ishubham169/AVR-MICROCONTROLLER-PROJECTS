#define F_CPU 8000000UL
#include<util/delay.h>

#include <avr/io.h>

int main(void)
{
	DDRD=0xFF;
	DDRB=(1<<4)|(1<<5);

	SPCR=SPCR|(1<<SPE);
	SPSR=SPSR|(1<<WCOL);
	while(1)
	{
		PORTD=SPDR;
		
	}
}