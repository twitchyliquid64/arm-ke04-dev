/**
 * KE04 Loading Firmware
 * Low-level system initialization
 *
 * Originally by Kevin Cuzner
 * Modified by twitchyliquid64 to ____________
 */
    .syntax unified
    .thumb

    .section ".interrupt_vector_table"
    .global __interrupt_vector_table

 __interrupt_vector_table:
    .long   _top_stack          /* marks the top of stack */
    .long   Reset_Handler       /* initial program counter */
    .long   NMI_Handler
    .long   HardFault_Handler
    .long   0 /* Reserved */
    .long   0 /* Reserved */
    .long   0 /* Reserved */
    .long   0 /* Reserved */
    .long   0 /* Reserved */
    .long   0 /* Reserved */
    .long   0 /* Reserved */
    .long   SVC_Handler
    .long   0 /* Reserved */
    .long   0 /* Reserved */
    .long   PendSV_Handler
    .long   SysTick_Handler

    /* KE04 Vector declarations */

    .long   0
    .long   0
    .long   0
    .long   0
    .long   0
    .long   FTMRE_IRQHandler    /* 21: FTMRE Command Complete */
    .long   PMC_IRQHandler      /* 22: PMC Low-voltage detect, low-voltage warning */
    .long   IRQ_IRQHandler      /* 23: Extrenal interrupt */
    .long   I2C0_IRQHandler     /* 24: I2C0 */
    .long   0
    .long   SPI0_IRQHandler     /* 26: SPI0 */
    .long   0
    .long   UART0_IRQHandler    /* 28: UART0 Status and error */
    .long   0
    .long   0
    .long   ADC0_IRQHandler     /* 31: ADC conversion complete */
    .long   ACMP0_IRQHandler    /* 32: Analog comparator 0 */
    .long   FTM0_IRQHandler     /* 33: FTM0 */
    .long   0
    .long   FTM2_IRQHandler     /* 35: FTM2 */
    .long   RTC_IRQHandler      /* 36: RTC overflow */
    .long   ACMP1_IRQHandler    /* 37: Analog comparator 1 */
    .long   PIT_CH0_IRQHandler  /* 38: PIT CH0 overflow */
    .long   PIT_CH1_IRQHandler  /* 39: PIT CH1 overflow */
    .long   KBI0_IRQHandler     /* 40: Keyboard interrupt 0 */
    .long   KBI1_IRQHandler     /* 41: Keyboard interrupt 1 */
    .long   0
    .long   ICS_IRQHandler      /* 43: Clock loss of clock */
    .long   WDOG_IRQHandler     /* 44: Watchdog timeout */
    .long   PWT_IRQHandler      /* 45: PWT */
    .long   0
    .long   0

    .section ".unsecured_config"
    .long   0xffffffff
    .long   0xffffffff
    .long   0xffffffff
    .long   0xfffeffff

/* Weak declarations */
    .thumb

    .weak	NMI_Handler
    .weak	HardFault_Handler
    .weak	SVC_Handler
    .weak	PendSV_Handler
    .weak	SysTick_Handler
    .weak   FTMRE_IRQHandler
    .weak   PMC_IRQHandler
    .weak   IRQ_IRQHandler
    .weak   I2C0_IRQHandler
    .weak   SPI0_IRQHandler
    .weak   UART0_IRQHandler
    .weak   ADC0_IRQHandler
    .weak   ACMP0_IRQHandler
    .weak   FTM0_IRQHandler
    .weak   FTM2_IRQHandler
    .weak   RTC_IRQHandler
    .weak   ACMP1_IRQHandler
    .weak   PIT_CH0_IRQHandler
    .weak   PIT_CH1_IRQHandler
    .weak   KBI0_IRQHandler
    .weak   KBI1_IRQHandler
    .weak   ICS_IRQHandler
    .weak   WDOG_IRQHandler
    .weak   PWT_IRQHandler

    .thumb
    .section ".startup","x",%progbits
    .thumb_func
    .global _startup
Reset_Handler:
_startup:
    // Disable the watchdog
    // We have to write to all regs except WIN
    ldr r0, =0x40052002 //Address of WDOG_CNT
    ldr r1, =0x20C5     //First unlock word
    strh r1,[r0]
    ldr r1, =0x28D9     //Second unlock word
    strh r1,[r0]

    //on every cycle we pet the dog
    //NOTE: We cannot use an interrupt to reset the watchdog.
    //It causes a hard fault or something that cuases the CPU to reset :(
    //__disable_irq();
    //WDOG->CNT = 0x02A6;
    //WDOG->CNT = 0x80B4;
    //__enable_irq();

    ldr r0, =0x40052000 //set CS1 to 0 (disable)
    ldr r1, =0x0
    strb r1,[r0]

    ldr r0, =0x40052001 //Address of CS2
    ldr r1, =0x01 //Defaults - leave it on 1Khz clock
    strb r1,[r0]

    ldr r0, =0x40052004 //Address of WDOG_TOVAL
    ldr r1, =0x1
    strh r1,[r0]

    /* Initialize GPRs */
    ldr r0,=0
    ldr r1,=0
    ldr r2,=0
    ldr r3,=0
    ldr r4,=0
    ldr r5,=0
    ldr r6,=0
    ldr r7,=0



    /* Handoff to C startup */
    ldr r0,=startup
    blx r0
    b   .


/* Stub handlers */

NMI_Handler:
    b   .
HardFault_Handler:
    b   .
SVC_Handler:
    b   .
PendSV_Handler:
    b   .
SysTick_Handler:
    b   .

/* Default handlers */
FTMRE_IRQHandler:
PMC_IRQHandler:
IRQ_IRQHandler:
I2C0_IRQHandler:
SPI0_IRQHandler:
UART0_IRQHandler:
ADC0_IRQHandler:
ACMP0_IRQHandler:
FTM0_IRQHandler:
FTM2_IRQHandler:
RTC_IRQHandler:
ACMP1_IRQHandler:
PIT_CH0_IRQHandler:
PIT_CH1_IRQHandler:
KBI0_IRQHandler:
KBI1_IRQHandler:
ICS_IRQHandler:
WDOG_IRQHandler:
PWT_IRQHandler:
    b   .
