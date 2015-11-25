#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{


	// Config output
	DDRD &= ~(_BV(PD2)) |  ~(_BV(PD3));  
 	PORTD|= _BV(PD2) | _BV(PD3); //Wyzerowanie portu guzika


	DDRB |= _BV(PB3) | _BV(PB2);  // output diody na PB3 (bo OC2)

	TCCR0 = (1<<WGM00) | (1 << WGM01) | (1<<COM01) | (1<<CS01); // Konfiguracja przerwań

	DDRB = 0xFF;	

	sei(); // uruchamiamy przerwania
	OCR0 = 0;
	_delay_ms(500);
	while (1)
	{
		if((PIND) &(1 << PD2)){ // obsługa rozświetlania 
			OCR0 += 2;
			_delay_ms(100);	
		}
		if((PIND) &(1 << PD3)){ //obsługa gaszenia			
		OCR0 -= 2;		
		_delay_ms(100);
	  }
     }
}
