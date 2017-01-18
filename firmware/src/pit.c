#include "MKE04Z4.h"
#include "pit.h"
#include <stdint.h>


/**
 * Sets up the PIT module to fire an interrupt twice a millisecond.
 * As per startup.c, our clock is 48Mhz.
 * As such, our interval is 24Mhz / 1000 / 2
 * LDVAL = 48000000: 1hz
 * LDVAL = 48000: 1000hz
 * LDVAL = 24000: 2000hz
 */
void  setup_PIT(uint32_t timeout)
{
    SIM->SCGC |= SIM_SCGC_PIT_MASK;                   //Turn on the clock for the PIT
    PIT->MCR = 0;                                     //Enable the PIT.
    PIT->CHANNEL[0].LDVAL = timeout;                    //Load the timeout value.
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK;       //Enable timer interrupts
    PIT->CHANNEL[0].TFLG = 0x1;                       //Clear the 'has interrupted' flag
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;      //Enable the timer.
    NVIC->ISER[0] = 1 << 22;                          //Enable IRQ channel 2 - PIT CH0.
}

uint32_t volatile counter;

// Called when PIT Channel 0 fires.
void PIT_CH0_IRQHandler(void)
{
    PIT->CHANNEL[0].TFLG = 0x1; //reset the trigger so it can fire again.
    counter++;
}

uint32_t getTicks()
{
  return counter;
}

void delayms(uint32_t ms){
  uint32_t needTicks = ms * 2;

  uint32_t startTicks = getTicks();
  while ((startTicks+needTicks) > getTicks());
}
