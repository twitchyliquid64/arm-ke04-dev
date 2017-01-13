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
    ics_setup();

#if DEBUG
    //enable GPIO
    GPIOA->PIDR |= 1 << 8;
    GPIOA->PDDR |= 1 << 8;
    GPIOA->PSOR |= 1 << 8;

    SIM->SCGC |= SIM_SCGC_PIT_MASK;
    PIT->MCR = 0;
    PIT->CHANNEL[0].LDVAL = 12000000U;
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK;
    PIT->CHANNEL[0].TFLG = 0x1;
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
    NVIC->ISER[0] = 1 << 22;
#endif
    __enable_irq();



    while (1)
    {
        //TODO: Do something here.

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
