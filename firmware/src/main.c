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
        uint32_t ticks = getTicks();
        while ((ticks+1000) > getTicks());
        GPIOA->PTOR |= 1 << 17;

        //on every cycle we pet the dog
        //NOTE: We cannot use an interrupt to reset the watchdog.
        //It causes a hard fault or something that cuases the CPU to reset :(
        //__disable_irq();
        //WDOG->CNT = 0x02A6;
        //WDOG->CNT = 0x80B4;
        //__enable_irq();
    }

    return 0;
}
