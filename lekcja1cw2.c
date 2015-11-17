#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{    
    DDRA |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);
    
    PORTA = 0x01;
    while(1)
    {
        while(PORTA != 0x80){
            _delay_ms(500);
            PORTA <<= 1;
        }
        while(PORTA !=0x01){
            _delay_ms(500);
            PORTA >>= 1;
        }
        

    }
}

