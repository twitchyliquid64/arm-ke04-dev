#include "MKE04Z4.h"
#include "pit.h"
#include <stdint.h>


/**
 * Sets up the ADC module
 */
void setup_ADC(void)
{
  SIM->SCGC |= SIM_SCGC_ADC_MASK;    //Turn on the clock for the ADC

  ADC->APCTL1 |= ADC_APCTL1_ADPC(8); //Disable I/O on the ADC pin.

  ADC->SC3 = ADC_SC3_ADICLK(1) |     //Bus clock / 2
             ADC_SC3_ADIV(3);        //Further divided by 8

  ADC->SC2  |= ADC_SC2_REFSEL(0);    //Default voltage reference
                                     //Software triggered (default)
}




uint8_t get_ADC(){
  //Set channel: AD8 == PTC0 & triggers the conversion
  ADC->SC1 = ADC_SC1_ADCH(8);
  while ((ADC->SC1 & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);
  return ADC->R;
}
