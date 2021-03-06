/*
******************************************************************************
File:     startup_MKE06Z4.s
Info:     Generated by Atollic TrueSTUDIO(R) 8.0.0   2017-07-05

The MIT License (MIT)
Copyright (c) 2009-2017 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.global Reset_Handler
.global InterruptVector
.global Default_Handler

/* Linker script definitions */
/* start address for the initialization values of the .data section */
.word _sidata
/* start address for the .data section */
.word _sdata
/* end address for the .data section */
.word _edata
/* start address for the .bss section */
.word _sbss
/* end address for the .bss section */
.word _ebss


/**
**===========================================================================
**  Program - Reset_Handler
**  Abstract: This code gets called after reset.
**===========================================================================
*/
  .section  .text.Reset_Handler,"ax", %progbits
  .type Reset_Handler, %function
Reset_Handler:
  /* Set stack pointer */
  ldr   r0, =_estack
  mov   sp, r0

  /* Branch to SystemInit function */
  bl SystemInit

  /* Copy data initialization values */
  ldr r1,=_sidata
  ldr r2,=_sdata
  ldr r3,=_edata
  b cmpdata
CopyLoop:
  ldr r0, [r1]
  str r0, [r2]
  adds r1, r1, #4
  adds r2, r2, #4
cmpdata:
  cmp r2, r3
  blt CopyLoop

  /* Clear BSS section */
  movs r0, #0
  ldr r2,=_sbss
  ldr r3,=_ebss
  b cmpbss
ClearLoop:
  str r0, [r2]
  adds r2, r2, #4
cmpbss:
  cmp r2, r3
  blt ClearLoop

  /* Call static constructors */
  bl __libc_init_array

  /* Branch to main */
  bl main

  /* If main returns, branch to Default_Handler. */
  b Default_Handler

  .size  Reset_Handler, .-Reset_Handler

/**
**===========================================================================
**  Program - Default_Handler
**  Abstract: This code gets called when the processor receives an
**    unexpected interrupt.
**===========================================================================
*/
  .section  .text.Default_Handler,"ax", %progbits
Default_Handler:
  b  Default_Handler

  .size  Default_Handler, .-Default_Handler

/**
**===========================================================================
**  Interrupt vector table
**===========================================================================
*/
  .section .isr_vector,"a", %progbits
InterruptVector:
  .word _estack                   /* 0 - Stack pointer */
  .word Reset_Handler             /* 1 - Reset */
  .word NMI_Handler               /* 2 - NMI  */
  .word HardFault_Handler         /* 3 - Hard fault */
  .word 0                         /* 4 - Reserved */
  .word 0                         /* 5 - Reserved */
  .word 0                         /* 6 - Reserved */
  .word 0                         /* 7 - Reserved */
  .word 0                         /* 8 - Reserved */
  .word 0                         /* 9 - Reserved */
  .word 0                         /* 10 - Reserved */
  .word SVC_Handler               /* 11 - SVCall */
  .word 0                         /* 12 - Reserved */
  .word 0                         /* 13 - Reserved */
  .word PendSV_Handler            /* 14 - PendSV */
  .word SysTick_Handler           /* 15 - Systick */

  /* External Interrupts */
  .word Reserved16_IRQHandler
  .word Reserved17_IRQHandler
  .word Reserved18_IRQHandler
  .word Reserved19_IRQHandler
  .word Reserved20_IRQHandler
  .word FTMRE_IRQHandler
  .word PMC_IRQHandler
  .word IRQ_IRQHandler
  .word I2C0_IRQHandler
  .word I2C1_IRQHandler
  .word SPI0_IRQHandler
  .word SPI1_IRQHandler
  .word UART0_IRQHandler
  .word UART1_IRQHandler
  .word UART2_IRQHandler
  .word ADC_IRQHandler
  .word ACMP0_IRQHandler
  .word FTM0_IRQHandler
  .word FTM1_IRQHandler
  .word FTM2_IRQHandler
  .word RTC_IRQHandler
  .word ACMP1_IRQHandler
  .word PIT_CH0_IRQHandler
  .word PIT_CH1_IRQHandler
  .word KBI0_IRQHandler
  .word KBI1_IRQHandler
  .word Reserved42_IRQHandler
  .word ICS_IRQHandler
  .word WDOG_IRQHandler
  .word PWT_IRQHandler
  .word MSCAN_RX_IRQHandler
  .word MSCAN_TX_IRQHandler


/**
**===========================================================================
**  Flash configuration field
**===========================================================================
*/
.section .flash_cfg,"a", %progbits
FlashConfig:
  .word 0xffffffff     /* 0x400 Backdoor Comparison Key */
  .word 0xffffffff     /* 0x404 Backdoor Comparison Key */
  .word 0xffffffff     
  .word 0xfffffffe     


/**
**===========================================================================
**  Weak interrupt handlers redirected to Default_Handler. These can be
**  overridden in user code.
**===========================================================================
*/
  .weak NMI_Handler
  .thumb_set NMI_Handler, Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler, Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler, Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler, Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler, Default_Handler

  .weak Reserved16_IRQHandler
  .thumb_set Reserved16_IRQHandler, Default_Handler

  .weak Reserved17_IRQHandler
  .thumb_set Reserved17_IRQHandler, Default_Handler

  .weak Reserved18_IRQHandler
  .thumb_set Reserved18_IRQHandler, Default_Handler

  .weak Reserved19_IRQHandler
  .thumb_set Reserved19_IRQHandler, Default_Handler

  .weak Reserved20_IRQHandler
  .thumb_set Reserved20_IRQHandler, Default_Handler

  .weak FTMRE_IRQHandler
  .thumb_set FTMRE_IRQHandler, Default_Handler

  .weak PMC_IRQHandler
  .thumb_set PMC_IRQHandler, Default_Handler

  .weak IRQ_IRQHandler
  .thumb_set IRQ_IRQHandler, Default_Handler

  .weak I2C0_IRQHandler
  .thumb_set I2C0_IRQHandler, Default_Handler

  .weak I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler, Default_Handler

  .weak SPI0_IRQHandler
  .thumb_set SPI0_IRQHandler, Default_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler, Default_Handler

  .weak UART0_IRQHandler
  .thumb_set UART0_IRQHandler, Default_Handler

  .weak UART1_IRQHandler
  .thumb_set UART1_IRQHandler, Default_Handler

  .weak UART2_IRQHandler
  .thumb_set UART2_IRQHandler, Default_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler, Default_Handler

  .weak ACMP0_IRQHandler
  .thumb_set ACMP0_IRQHandler, Default_Handler

  .weak FTM0_IRQHandler
  .thumb_set FTM0_IRQHandler, Default_Handler

  .weak FTM1_IRQHandler
  .thumb_set FTM1_IRQHandler, Default_Handler

  .weak FTM2_IRQHandler
  .thumb_set FTM2_IRQHandler, Default_Handler

  .weak RTC_IRQHandler
  .thumb_set RTC_IRQHandler, Default_Handler

  .weak ACMP1_IRQHandler
  .thumb_set ACMP1_IRQHandler, Default_Handler

  .weak PIT_CH0_IRQHandler
  .thumb_set PIT_CH0_IRQHandler, Default_Handler

  .weak PIT_CH1_IRQHandler
  .thumb_set PIT_CH1_IRQHandler, Default_Handler

  .weak KBI0_IRQHandler
  .thumb_set KBI0_IRQHandler, Default_Handler

  .weak KBI1_IRQHandler
  .thumb_set KBI1_IRQHandler, Default_Handler

  .weak Reserved42_IRQHandler
  .thumb_set Reserved42_IRQHandler, Default_Handler

  .weak ICS_IRQHandler
  .thumb_set ICS_IRQHandler, Default_Handler

  .weak WDOG_IRQHandler
  .thumb_set WDOG_IRQHandler, Default_Handler

  .weak PWT_IRQHandler
  .thumb_set PWT_IRQHandler, Default_Handler

  .weak MSCAN_RX_IRQHandler
  .thumb_set MSCAN_RX_IRQHandler, Default_Handler

  .weak MSCAN_TX_IRQHandler
  .thumb_set MSCAN_TX_IRQHandler, Default_Handler

  .end
