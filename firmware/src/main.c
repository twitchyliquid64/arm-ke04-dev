/**
 * Main
 *
 * based on work by Kevin Cuzner
 * Modified by meh
 */

#include "MKE04Z4.h"



/**
 * Sets up the ICS module to FEI at approximately 48MHz with the peripheral
 * clock at 24MHz
 */
static void ics_setup(void)
{
    //we assume this is run soon after setup
    ICS->C2 = 0x00; //bdiv=0
    ICS->C1 = 0x04; //internal reference clock to FLL
}


int main()
{
    //set up the clock to our known 48MHz frequency
    //ics_setup();

    //__enable_irq(); //Whats this for

    GPIOA->PIDR |= 1 << 17;
    GPIOA->PDDR |= 1 << 17;
    GPIOA->PSOR |= 1 << 17;
    uint32_t volatile soFar = 0;

    while (1)
    {
        soFar++;
        if (soFar > 999999){
          GPIOA->PTOR |= 1 << 17;
          soFar = 0;
        }

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

#if DEBUG
void PIT_CH0_IRQHandler(void)
{
    PIT->CHANNEL[0].TFLG = 0x1;
    GPIOA->PTOR = 1 << 8;
}
#endif
