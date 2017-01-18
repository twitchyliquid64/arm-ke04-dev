#if !defined(PIT_M)
#define PIT_M
#include <stdint.h>

void  setup_PIT(uint32_t timeout);
uint32_t getTicks();
void delayms(uint32_t ms);

#define PIT_2kHz 24000
#define PIT_1kHz 48000
#define PIT_1Hz 48000000

#endif
