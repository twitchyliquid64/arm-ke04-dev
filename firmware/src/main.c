/**
 * Main
 *
 * based on work by Kevin Cuzner
 * Modified by meh
 */

 #include "MKE04Z4.h"
 #include "pit.h"
 #include <stdint.h>



void setup()
{
    GPIOA->PIDR |= 1 << 17;
    GPIOA->PDDR |= 1 << 17;
    GPIOA->PSOR |= 1 << 17;
}


int main()
{
    while (1)
    {
        uint8_t adc_val = get_ADC();
        delayms(adc_val);
        GPIOA->PTOR |= 1 << 17;
    }

    return 0;
}
