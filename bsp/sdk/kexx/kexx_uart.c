/** @file
 *  @brief Implementation of UART IRQ Handlers.
 */

/** @addtogroup UART
 *  @{ */

#include <kexx_uart.h>
#include <stdlib.h>

/** @name Callback handlers
 *  @{ */
UARTCallbackFcn_t CallbackUART0 = NULL; /**< Callback for UART 0. */
UARTCallbackFcn_t CallbackUART1 = NULL; /**< Callback for UART 1. */
UARTCallbackFcn_t CallbackUART2 = NULL; /**< Callback for UART 2. */
/** @} */

/* Controls interrupt settings for UART. */
void UART_interruptControl(const UARTModule_t* const mod, const UARTInterrupt_t irq)
{
    if (NULL == mod->callback)
    {
        return; /* sanity check */
    }

    /* setup callback handler */
    switch ((uint32_t) mod->base)
    {
        case UART0_BASE:
            CallbackUART0 = mod->callback;
            if (irq != kUART_INTERRUPT_DISABLE)
            {
                NVIC_EnableIRQ(UART0_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(UART0_IRQn);
            }
            break;

        case UART1_BASE:
            CallbackUART1 = mod->callback;
            if (irq != kUART_INTERRUPT_DISABLE)
            {
                NVIC_EnableIRQ(UART1_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(UART1_IRQn);
            }
            break;

        case UART2_BASE:
            CallbackUART2 = mod->callback;
            if (irq != kUART_INTERRUPT_DISABLE)
            {
                NVIC_EnableIRQ(UART2_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(UART2_IRQn);
            }
            break;

        default:
            return; /* invalid base */
    }

    /* enable/disable interrupts */
    if (irq & kUART_INTERRUPT_ENABLE_TX)
    {
         mod->base->C2 |= UART_C2_TIE_MASK;
    }
    else
    {
        mod->base->C2 &= ~UART_C2_TIE_MASK;
    }

    if (irq & kUART_INTERRUPT_ENABLE_TX_COMPLETE)
    {
        mod->base->C2 |= UART_C2_TCIE_MASK;
    }
    else
    {
        mod->base->C2 &= ~UART_C2_TCIE_MASK;
    }

    if (irq & kUART_INTERRUPT_ENABLE_RX)
    {
        mod->base->C2 |= UART_C2_RIE_MASK;
    }
    else
    {
        mod->base->C2 &= ~UART_C2_RIE_MASK;
    }

    if (irq & kUART_INTERRUPT_ENABLE_IDLE)
    {
        mod->base->C2 |= UART_C2_ILIE_MASK;
    }
    else
    {
        mod->base->C2 &= ~UART_C2_ILIE_MASK;
    }
}

/* Initialises the UART. */
void UART_init(const UARTModule_t* const mod)
{
    /* Initialise system integration module pin select settings. */
    switch ((uint32_t) mod->base)
    {
        case UART0_BASE:
            /* Pinout. */
            if (kUART_PS0 == mod->pinout)
            {
                SIM->PINSEL &= ~SIM_PINSEL_UART0PS_MASK;
            }
            else
            {
                SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;
            }
            /* Enable clock. */
            SIM->SCGC |= SIM_SCGC_UART0_MASK;
            break;

        case UART1_BASE:
            if (kUART_PS0 == mod->pinout)
            {
                SIM->PINSEL1 &= ~SIM_PINSEL1_UART1PS_MASK;
            }
            else
            {
                SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK;
            }
            SIM->SCGC |= SIM_SCGC_UART1_MASK;
            break;

        case UART2_BASE:
            if (kUART_PS0 == mod->pinout)
            {
                SIM->PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK;
            }
            else
            {
                SIM->PINSEL1 |= SIM_PINSEL1_UART2PS_MASK;
            }
            SIM->SCGC |= SIM_SCGC_UART2_MASK;
            break;

        default:
            return; /* invalid module base */
    }

    /* make sure tx and rx are disabled */
    mod->base->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

    /* configure uart mode, 8-bit or 9-bit */
    if (kUART_8bit == mod->mode)
    {
        mod->base->C1 &= ~UART_C1_M_MASK;
    }
    else
    {
        mod->base->C1 |= UART_C1_M_MASK;
    }

    /* setup parity */
    if (kUART_NO_PARITY == mod->parity)
    {
        mod->base->C1 &= ~(UART_C1_PE_MASK | UART_C1_PT_MASK);
    }
    else
    {
        mod->base->C1 |= UART_C1_PE_MASK;

        if (mod->parity == kUART_ODD)
        {
            mod->base->C1 |= UART_C1_PT_MASK;
        }
        else
        {
            mod->base->C1 &= ~UART_C1_PT_MASK;
        }
    }

    /* specify invert of lines */
    if (kUART_TXINV_INVERT == mod->invertTx)
    {
        mod->base->C3 |= UART_C3_TXINV_MASK;
    }
    else
    {
        mod->base->C3 &= ~UART_C3_TXINV_MASK;
    }

    if (kUART_RXINV_INVERT == mod->invertRx)
    {
        mod->base->S2 |= UART_S2_RXINV_MASK;
    }
    else
    {
        mod->base->S2 &= ~UART_S2_RXINV_MASK;
    }

    /* configure baud */
    uint16_t sbr = ((SystemCoreClock / 32) / mod->baudrate);
    mod->base->BDH = (~UART_BDH_SBR_MASK) | ((sbr >> 8u) & UART_BDH_SBR_MASK); /* high bits */
    mod->base->BDL = (sbr & UART_BDL_SBR_MASK); /* low bits */

    /* set stop bits */
    if (kUART_SBNS_ONE_STOP_BIT == mod->stopBits)
    {
        mod->base->BDH &= ~UART_BDH_SBNS_MASK;
    }
    else
    {
        mod->base->BDH |= UART_BDH_SBNS_MASK;
    }

    /* enable transmitter */
    mod->base->C2 |= UART_C2_TE_MASK;
    /* enable receiver */
    mod->base->C2 |= UART_C2_RE_MASK;

    /* setup callback function */
    UART_interruptControl(mod, mod->irq);
}

void UART_transmitBlocking(const UARTModule_t* const umod, const uint8_t *string, uint32_t len)
{
    while ((len--) > 0)
    {
        while (!(umod->base->S1 & UART_S1_TDRE_MASK))
        {
            /* wait until we can write to register */
        }
        umod->base->D = (uint8_t) *(string++); /* write data */
    }
    while (!(umod->base->S1 & UART_S1_TC_MASK))
    {
        /* wait until transmission complete */
    }
}

/** @brief Stubby for UART0 ISR. */
void UART0_IRQHandler(void)
{
    CallbackUART0();
}

/** @brief Stubby for UART1 ISR. */
void UART1_IRQHandler(void)
{
    CallbackUART1();
}

/** @brief Stubby for UART2 ISR. */
void UART2_IRQHandler(void)
{
    CallbackUART2();
}

/** @} *//* end group */

