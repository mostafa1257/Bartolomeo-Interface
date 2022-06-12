// example program for launchpad, blink two leds, how original!

#include <msp430.h>
#include "FreeRTOS.h"
#include "task.h"

int main()
{
	WDTCTL = WDTPW | WDTHOLD;
}
