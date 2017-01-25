#include "MKE04Z4.h"
#include "uart.h"
#include <stdint.h>

volatile uint8_t UART_RECV_BUFF[UART_RECV_BUFF_SIZE];
volatile uint8_t UART_RECV_HEAD_INDEX;
volatile uint8_t UART_RECV_TAIL_INDEX;
volatile uint8_t UART_RECV_HAS_DATA;

uint8_t push_recv_val(uint8_t character){
  if (UART_RECV_HEAD_INDEX == UART_RECV_TAIL_INDEX && UART_RECV_HAS_DATA == 1){
    return 1; //no capacity
  }
  UART_RECV_HAS_DATA = 1;
  UART_RECV_BUFF[UART_RECV_HEAD_INDEX] = character;
  UART_RECV_HEAD_INDEX++;
  if (UART_RECV_HEAD_INDEX == UART_RECV_BUFF_SIZE)
    UART_RECV_HEAD_INDEX = 0;

  return 0;
}

uint8_t availableUART(){
  return UART_RECV_HAS_DATA;
}

uint8_t readUART(){
  while(UART_RECV_HAS_DATA == 0);;
  uint8_t data = UART_RECV_BUFF[UART_RECV_TAIL_INDEX];
  UART_RECV_TAIL_INDEX++;
  if (UART_RECV_TAIL_INDEX == UART_RECV_BUFF_SIZE)
    UART_RECV_TAIL_INDEX = 0;
  if (UART_RECV_TAIL_INDEX == UART_RECV_HEAD_INDEX)
    UART_RECV_HAS_DATA = 0;

  return data;
}

void writeUART_str(char* str){
  while(*str != '\0'){
    writeUART(*str);
    str++;
  }
}

void writeUART(uint8_t ch){
  UART0->D = ch;
  while(!(UART0->S1 & UART_S1_TDRE_MASK));
}

void  setup_UART(){
  //cuz we cant garrantee BSS is set to 0.
  UART_RECV_HEAD_INDEX = 0;
  UART_RECV_HAS_DATA = 0;
  UART_RECV_TAIL_INDEX = 0;

  //Baud rate = Bus Clk / (16 * divider)
  //9615 = 48000000 / (16 * 312)
  //Close enough to 9600
  uint16_t baud_rate_divider_setting = 312;

  SIM->SCGC |= SIM_SCGC_UART0_MASK;                          //Enable the clock for the UART Peripheral

  UART0->BDH = UART_BDH_SBR(baud_rate_divider_setting >> 8);
  UART0->BDL = UART_BDL_SBR(baud_rate_divider_setting);      //Set the bottom bits for the baud rate - applies BDH too.

  //Enable RI (Recieve int)
  //Transmitter Enable (TE) & Reciever Enable (RE)
  //Recieve interrupt fires when Recieve Data Register Full (RDRF) flag is set.
  UART0->C2 =  UART_C2_RIE_MASK | UART_C2_RE_MASK;

  UART0->C2 |=  UART_C2_TE_MASK;

  //Unmask interrupts on UART0 vector.
  NVIC->ISER[0] = 1 << 12;

}

// Called when UART0 interrupt fires.
void UART0_IRQHandler(void)
{
  if((UART0->S1 & UART_S1_RDRF_MASK) == UART_S1_RDRF_MASK){ //Recieved byte
    push_recv_val(UART0->D);
  }
}
