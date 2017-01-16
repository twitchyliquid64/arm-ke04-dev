/**
 * KE04 Loading Firmware
 * Mid-level startup code
 *
 * originally by Kevin Cuzner
 * modified by meh
 */

#include "MKE04Z4.h"
#include <stdint.h>

/**
 * Sets up the ICS module to FEI at approximately 48MHz with the peripheral
 * clock at 24MHz
 */
static void setup_ICS(void)
{
    //we assume this is run soon after setup
    ICS->C2 = 0x00; //bdiv=0
    ICS->C1 = 0x04; //internal reference clock to FLL
}



extern uint32_t _start_bss, _end_bss, _start_data, _data_size, _data_flash_addr;

void startup()
{
    /* Zero the BSS */
    uint32_t *dest;
    for (dest = &_start_bss; dest < &_end_bss; dest++)
        *dest = 0;

    setup_ICS(); //set up the clock to our known 48MHz frequency
    setup_PIT();

    main();
}
