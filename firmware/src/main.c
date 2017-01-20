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
    //Setup the pins for our LED.
    GPIOA->PIDR |= (1 << 17);
    GPIOA->PDDR |= (1 << 17);
    GPIOA->PSOR |= (1 << 17);
}

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main()
{
    while (1)
    {
        uint8_t adc_val = get_ADC();

        uint16_t pwm_val = map(adc_val, 0, 255, 100, 2960);
        pwm_set_amount(pwm_val);

        delayms(adc_val);
        GPIOA->PTOR |= 1 << 17;
    }

    return 0;
}
