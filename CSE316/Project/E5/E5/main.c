/*
 * E5.c
 *
 * Created: 4/23/2017 2:55:28 PM
 * Author : graphics
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
void drawCharRed(unsigned char *);
void drawCharRedRotate(unsigned char *, int);
void drawBlank();
unsigned char ROL(unsigned char, int);
unsigned char zed[] = {
	0b11111111,
	0b10000001,
	0b11011111,
	0b11101111,
	0b11110111,
	0b11111011,
	0b10000001,
	0b11111111
};

int main(void)
{
    /* Replace with your application code */
	DDRA=0xff;//positive row
	DDRD=0xff;//negative column red
    while (1) 
    {
		for (int i = 0; i < 8;i++)
		{
			drawCharRedRotate(zed, i);	
		}
		//drawBlank();	
		//_delay_ms(200);
    }
}

void drawCharRedRotate(unsigned char* character, int shift)
{
	long i;
	for (i=0; i<10; i++)
	{
		int j;
		unsigned char row = 0b00000001;
		for (j=0; j<8; j++)
		{
			PORTD = ROL(row, j);
			PORTA = character[(j + shift)%8];
			_delay_ms(1);
		}
		
	}	
}

void drawBlank()
{
	PORTA = 0xff;
	PORTD = 0x00;
	_delay_ms(300);
}
void drawCharRed(unsigned char *character)
{
	long i;
	for (i=0; i<10; i++)
	{
		int j;
		unsigned char row = 0b00000001;
		for (j=0; j<8; j++)
		{
			PORTD = ROL(row, j);
			PORTA = character[j];
			_delay_ms(1);
		}
		
	}
}
unsigned char ROL(unsigned char number, int shiftAmount)
{
	int i;
	for (i=0; i<shiftAmount; i++)
	{
		unsigned char MSB = number & 0b10000000;
		MSB = MSB >> 7;
		number = number << 1;
		number = number | MSB;
	}
	return number;
}

