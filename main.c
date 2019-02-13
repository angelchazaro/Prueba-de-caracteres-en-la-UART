/*
 * Prueba de comandos AT.c
 *
 * Created: 04/02/2019 08:34:57 p. m.
 * Author : dx_ch
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

char enter=13;
char suprimir=127;
char intro=12;
char retroceso=8;
char espacio=32;
char RecibeDato,bandera;

void Tx_char()
{
	//while((UCSR0A&0x60)==0);
	UCSR0A=0x60;
	UDR0=RecibeDato;
}

int main(void)
{
	UCSR0B=0x98;
	UCSR0C=0x06;
	UBRR0=103;
	sei();
    /* Replace with your application code */
    while (1) 
    {
		if (bandera==1)
		{
			Tx_char();
			bandera=0;
			//UDR0=enter;
		}	
    }
}

ISR(USART_RX_vect)
{
	RecibeDato=UDR0;
	
	if (RecibeDato==retroceso)
	{
		RecibeDato=retroceso;
	}
	if (RecibeDato==espacio)
	{
		RecibeDato=intro;
	}
	if (RecibeDato==enter)
	{
		UDR0=RecibeDato;
	}
	bandera=1;
}
