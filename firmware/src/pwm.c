#include "MKE04Z4.h"
#include "pwm.h"
#include <stdint.h>

//This code sets up PWM on pin PTA1.

void setup_PWM(void)
{
  //Turn on the clock for the FTM
  SIM->SCGC |= SIM_SCGC_FTM0_MASK;
  //PTA1 already connected to FTM0_CH1 (no write to PINSEL required)

  //System clock = 48 / 2 = 24Mhz.
  //Timer clock = 24Mhz/8 = 3Mhz.
  //Frequency: 3Mhz / 3000 = 1Khz.
  //The duty cycle is the ratio of MOD / CnV
  FTM0->MOD = 3000;

  //FTM0_CH1 is connected to PTA1, so we are using that.
  //FTM0_CH1 High true pulses on Edge aligned PWM
  FTM0->CONTROLS[1].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK; //No Interrupts; High True pulses on Edge Aligned PWM
  FTM0->CONTROLS[1].CnV  = 2700;

  // Setting the system clock selection starts the timer (which we do).
  FTM0->SC = FTM_SC_CLKS(1)    //System Clock
           | FTM_SC_PS(3);     //Divide by 8
}

//The Duty cycle as a percentage is amt / FTM0->MOD * 100.
void pwm_set_amount(uint16_t amt){
  FTM0->CONTROLS[1].CnV  = amt;
}
