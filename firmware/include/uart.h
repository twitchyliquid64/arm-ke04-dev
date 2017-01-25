#if !defined(UART_M)
#define UART_M
#include <stdint.h>

#define UART_RECV_BUFF_SIZE 32

uint8_t availableUART();
void  setup_UART();
uint8_t readUART();
#endif
