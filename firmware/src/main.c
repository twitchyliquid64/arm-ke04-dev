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
        writeUART_str("Open window\n");
        delayms(3000);
        writeUART_str("Close window\n");
        while(availableUART())
          writeUART(readUART());
    }

    return 0;
}
