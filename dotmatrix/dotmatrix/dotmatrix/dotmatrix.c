#define F_CPU 8000000
#include<avr/io.h>
#include<util/delay.h>



int main(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRC = 0x0F;
	
char PORT[8] = {1,2,4,8,16,32,64,128};


                static int ALPHA[26][8]={{0,0b01111111,0b11111111,0b11001100,0b11001100,0b11001100,0b11111111,0b01111111},
                {0,0b00111100,0b01111110,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},
                {0,0b11000011,0b11000011,0b11000011,0b11000011,0b11100111,0b01111110,0b00111100},
                {0,0b01111110,0b10111101,0b11000011,0b11000011,0b11000011,0b11111111,0b11111111},
                {0,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},
                {0,0b11011000,0b11011000,0b11011000,0b11011000,0b11011000,0b11111111,0b11111111},
                {0b00011111,0b11011111,0b11011000,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},
                {0,0b11111111,0b11111111,0b00011000,0b00011000,0b00011000,0b11111111,0b11111111},
                {0b11000011,0b11000011,0b11000011,0b11111111,0b11111111,0b11000011,0b11000011,0b11000011},
                {0b11000000,0b11000000,0b11000000,0b11111111,0b11111111,0b11000011,0b11001111,0b11001111},
                {0,0b11000011,0b11100111,0b01111110,0b00111100,0b00011000,0b11111111,0b11111111},
                {0b00000011,0b00000011,0b00000011,0b00000011,0b00000011,0b00000011,0b11111111,0b11111111},
                {0b11111111,0b11111111,0b01100000,0b01110000,0b01110000,0b01100000,0b11111111,0b11111111},
                {0b11111111,0b11111111,0b00011100,0b00111000,0b01110000,0b11100000,0b11111111,0b11111111},
                {0b01111110,0b11111111,0b11000011,0b11000011,0b11000011,0b11000011,0b11111111,0b01111110},
                {0,0b01110000,0b11111000,0b11001100,0b11001100,0b11001100,0b11111111,0b11111111},
                {0b01111110,0b11111111,0b11001111,0b11011111,0b11011011,0b11000011,0b11111111,0b01111110},
                {0b01111001,0b11111011,0b11011111,0b11011110,0b11011100,0b11011000,0b11111111,0b11111111},
                {0b11001110,0b11011111,0b11011011,0b11011011,0b11011011,0b11011011,0b11111011,0b01110011},
                {0b11000000,0b11000000,0b11000000,0b11111111,0b11111111,0b11000000,0b11000000,0b11000000},
                {0b11111110,0b11111111,0b00000011,0b00000011,0b00000011,0b00000011,0b11111111,0b11111110},
                {0b11100000,0b11111100,0b00011110,0b00000011,0b00000011,0b00011110,0b11111100,0b11100000},
                {0b11111110,0b11111111,0b00000011,0b11111111,0b11111111,0b00000011,0b11111111,0b11111110},
                {0b01000010,0b11100111,0b01111110,0b00111100,0b00111100,0b01111110,0b11100111,0b01000010},
                {0b01000000,0b11100000,0b01110000,0b00111111,0b00111111,0b01110000,0b11100000,0b01000000},
                {0b11000011,0b11100011,0b11110011,0b11111011,0b11011111,0b11001111,0b11000111,0b11000011}};
               
                                               
                char NAME[]={7,0,8,11,4,11,4,2,19,17,14,13,8,2,18};
                                uint8_t l =0;
                               
                while(1)
                {
 
 
for (int m=0;m<sizeof NAME;m++)
{
                l = NAME[m];
                for (int n=0;n<200;n++)
                {
                                for (int j=0;j<4;j++)
                                {
                                                PORTB = PORT[j];
                                                PORTD = ~ALPHA[l][j];
                                                _delay_us(500);
 
                                }
                                PORTB=0x00;
                                for (int k=0;k<4;k++)
                                {
                                                PORTC = PORT[k];
                                               
                                                PORTD = ~ALPHA[l][k+4];
                                                _delay_us(500);
 
                                }
                                PORTC=0x00;
 
                }
}
               
 
	 _delay_ms(220);
       _delay_ms(220);
    
 
                }
}