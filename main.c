#include "msp430.h"

int main()
{
	WDTCTL = WDTPW | WDTHOLD; // disable watchdog
	
	// GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN6 + GPIO_PIN7);
	P10DIR = (BIT7 | BIT6);
	P10OUT &= ~BIT7;
	P10OUT &= ~BIT6; // start with P1.0 on
	// P10OUT &= ~BIT6; // and P1.6 off
	
	// while(1) //switch between P1.0 and P1.6 every seconds, until heat death of the universe
	// {
		P10OUT = BIT6;
	// }

	return 0;
}