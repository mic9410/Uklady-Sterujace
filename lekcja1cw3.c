#define F_CPU 16000000UL     
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{    
    DDRA |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);
    
    PORTA = 0x01;
    int x = 750;
    while(1)
    {
    for(int i=0; i<x; i++){
         PORTA = 0xFF;
         int time = x-i;
         _delay_us(time);
         PORTA = 0x00;
         int secTime = i;
         _delay_us(secTime);
    }
    for(int i=0; i<x; i++){
        PORTA = 0xFF;
        int time = i;
        _delay_us(time);
        PORTA = 0x00;
        int secTime = x-i;
        _delay_us(secTime);
    }    
        
        
                

    }
}

