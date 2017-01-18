/**
 * Main
 *
 * based on work by Kevin Cuzner
 * Modified by meh
 */

 #include "MKE04Z4.h"
 #include "pit.h"
 #include <stdint.h>






int main()
{
    __enable_irq();

    GPIOA->PIDR |= 1 << 17;
    GPIOA->PDDR |= 1 << 17;
    GPIOA->PSOR |= 1 << 17;

    while (1)
    {
        delayms(1000);
        GPIOA->PTOR |= 1 << 17;
    }

    return 0;
}
