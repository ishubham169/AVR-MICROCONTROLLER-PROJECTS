#define F_CPU 8000000UL
#include<util/delay.h>
#include <avr/io.h>

int main(void)

{
	int i,y=0;
	DDRD=0x00;
	DDRB=0b00111111;
    PORTD=0xFF;
    while(1)
    {
		for(i=0;i<6;i++)
		{
			PORTB |=1<<i;
			_delay_ms(10);
			y=i;
			if((PIND&(1<<0))==0)
			{
				switch(y)
				{
					case 0:PORTB=0b00000001;
					_delay_ms(1000);
					break;
					case 1:PORTB=0b00000011;
					_delay_ms(1000);
					break;
					case 2:PORTB=0b00000111;
					_delay_ms(1000);
					break;
					case 3:PORTB=0b00001111;
					_delay_ms(1000);
					break;
					case 4:PORTB=0b00011111;
					_delay_ms(1000);
					break;
					case 5:PORTB=0b00111111;
					_delay_ms(1000);
					break;
				}
				
			}
	PORTB=0x00;
		}
		
		
		
		
		
		
		}}       
		
		