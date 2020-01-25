/*
 *  7-segment multiplexing
 * 
 *  RA0 = Left anode
 *  RA1 = Center anode
 *  RA2 = Right anode
 *  RA3 = Hex(1)/Dec(0) selector input
 *  
 *  PORTB = Data input
 *  PORTC = Cathode (DP,G,F,E,D,C,B,A)
 */

// CONFIG
#pragma config OSC = HS         // Oscillator selection bits (XT oscillator)
#pragma config WDT = OFF         // Watchdog timer enable bit (WDT enabled)
#pragma config CP = OFF         // Code protection bit (Code protection off)

#define _XTAL_FREQ 4000000

#include <xc.h>

unsigned char digits[16] = {192,249,164,176,153,146,130,216,128,144,136,131,198,161,134,142};

int main(void) {
    
    int t;
    
    TRISA = 0x08;   //RA3 = input else output
    TRISB = 0xFF;   //RB = input
    TRISC = 0x00;   //RC = output
    
    PORTA = 0x00;   //turn off all anodes
    PORTC = 0xFF;   //turn off all cathodes
    
    while(1)
    {
        if(RA3 == 1)    //hex
        {
            t = PORTB;
            
            //disable left
            RA0 = 1;
        
            //center
            PORTC = digits[t >> 4];
            RA1 = 0;
            __delay_ms(5);
            RA1 = 1;
            //__delay_ms(10);
            
            //right
            PORTC = digits[t & 0x0F];
            RA2 = 0;
            __delay_ms(5);
            RA2 = 1;
            //__delay_ms(10);
        }    
        else            //dec
        {
            t = PORTB;
        
            //left
            PORTC = digits[t / 100];
            t = t % 100;
            RA0 = 0;
            __delay_ms(5);
            RA0 = 1;
            //__delay_ms(10);
            
            //center
            PORTC = digits[t / 10];
            t = t % 10;
            RA1 = 0;
            __delay_ms(5);
            RA1 = 1;
            //__delay_ms(10);
            
            //right
            PORTC = digits[t];
            RA2 = 0;
            __delay_ms(5);
            RA2 = 1;
            //__delay_ms(10);
        }
    }
    
    return 0;
}
