#include "MKE04Z4.h"
#include "adc.h"
#include <stdint.h>


/**
 * Sets up the ADC module
 */
void setup_ADC(void)
{
  SIM->SCGC |= SIM_SCGC_ADC_MASK;    //Turn on the clock for the ADC

  ADC->APCTL1 |= ADC_APCTL1_ADPC(8); //Disable I/O on the ADC pin. For this board thats PTC0.
                                     //PTC0 default function is ADC so dont need to touch PINSEL.

  ADC->SC3 = ADC_SC3_ADICLK(1) |     //Bus clock / 2
             ADC_SC3_ADIV(3);        //Further divided by 8

  ADC->SC2  |= ADC_SC2_REFSEL(0);    //Default voltage reference
                                     //Software triggered (default)
}




uint8_t get_ADC(){
  //Set channel: AD8 == PTC0 & triggers the conversion
  ADC->SC1 = ADC_SC1_ADCH(8);
  //Spin waiting for conversion complete bit to be set
  while ((ADC->SC1 & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
  //Read the result (A read also clears the register)
  return ADC->R;
}
