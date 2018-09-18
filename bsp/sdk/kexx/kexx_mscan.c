/** @file
 *  @brief Implementation of the MSCAN Driver.
 */

/** @addtogroup MSCAN
 *  @{ */
#include <mcu.h>
#include <kexx_mscan.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define UNUSED(x) ((void)x)

static MSCAN_CallbackType MSCAN_RxCallback[1] = {(MSCAN_CallbackType)NULL};
static MSCAN_CallbackType MSCAN_TxCallback[1] = {(MSCAN_CallbackType)NULL};

void MSCAN_Isr(void);

/*----------------------------------------------------------------------------*/
/* Initialise the MSCAN module. */
void CAN_Init(MSCAN_Type *pCANx,MSCAN_ConfigPtr pCANConfig)
{
    uint8_t bTxIntEn = 0;

    SIM->SCGC |= SIM_SCGC_MSCAN_MASK;

    CAN_Enable(pCANx);

    if (pCANConfig->sSetting.bCLKSRC)
    {
        pCANx->CANCTL1 |= MSCAN_CANCTL1_CLKSRC_MASK;
    }

    CAN_InitialModeReq(pCANx);

    while (!CAN_IsInitialMode(pCANx))
    {
        /* Enter into Initialization mode. */
    }

    CAN_WriteIDAR0Reg(pCANx,(uint8_t *)&(pCANConfig->u32IDAR0));
    CAN_WriteIDAM0Reg(pCANx,(uint8_t *)&(pCANConfig->u32IDMR0));
    CAN_WriteIDAR1Reg(pCANx,(uint8_t *)&(pCANConfig->u32IDAR1));
    CAN_WriteIDAM1Reg(pCANx,(uint8_t *)&(pCANConfig->u32IDMR1));

    CAN_SetBaudRateReg(pCANx,pCANConfig->sBaudRateSetting);

    if (pCANConfig->sSetting.bListenModeEn)
    {
        CAN_ListenModeEn(pCANx);
    }
    else
    {
        CAN_ListenModeDisable(pCANx);
    }

    if (pCANConfig->sSetting.bLoopModeEn)
    {
        CAN_LoopModeEn(pCANx);
    }
    else
    {
        CAN_LoopModeDisable(pCANx);
    }

    if (pCANConfig->sSetting.bStopEn)
    {
        CAN_StopInWaitModeEn(pCANx);
    }
    else
    {
        CAN_StopInWaitModeDisable(pCANx);
    }

    if (pCANConfig->sSetting.bWUPM)
    {
        CAN_WakeUpModeFilter(pCANx);
    }
    else
    {
        CAN_WakeUpModeNoFilter(pCANx);
    }

    if (pCANConfig->sSetting.bBusOffUser)
    {
        CAN_BusOffUserRecovery(pCANx);
    }
    else
    {
        CAN_BusOffAutoRecovery(pCANx);
    }

    // set Identifier Acceptance Mode
    CAN_SetIDAMode(pCANx,pCANConfig->u8IDARMode);

    // exit initialization mode
    CAN_NormalModeReq(pCANx);

    while (CAN_IsInitialMode(pCANx))
    {
        /* Wait to exit initialization mode. */
    }

    if (pCANConfig->sSetting.bOverRunIEn)
    {
        CAN_OverrunIntEn(pCANx);
    }
    else
    {
        CAN_OverrunIntDisable(pCANx);
    }

    if (pCANConfig->sSetting.bRxFullIEn)
    {
        CAN_ReceiverFullIntEn(pCANx);
        NVIC_EnableIRQ(MSCAN_RX_IRQn);
    }
    else
    {
        CAN_ReceiverFullIntDisable(pCANx);
        NVIC_DisableIRQ(MSCAN_RX_IRQn);
    }

    if (pCANConfig->sSetting.bRxStatusChangeIEn)
    {
        CAN_ReceiverStatusChangeIntEn(pCANx);
        bTxIntEn = 1;
    }
    else
    {
        CAN_ReceiverStatusChangeIntDisable(pCANx);
    }

    if (pCANConfig->sSetting.bStatusChangeIEn)
    {
        CAN_StatusChangeIntEn(pCANx);
        bTxIntEn = 1;
    }
    else
    {
        CAN_StatusChangeIntDisable(pCANx);
    }

    if (pCANConfig->sSetting.bTimerEn)
    {
        CAN_TimerEn(pCANx);
    }
    else
    {
        CAN_TimerDisable(pCANx);
    }

    if (pCANConfig->sSetting.bTxEmptyIEn)
    {
        CAN_TransmitterEmptyIntEn(pCANx);
        bTxIntEn = 1;
    }
    else
    {
        CAN_TransmitterEmptyIntDisable(pCANx);
    }

    if (pCANConfig->sSetting.bTxStatusChangeIEn)
    {
        CAN_TransmitterStatusChangeIntEn(pCANx);
        bTxIntEn = 1;
    }
    else
    {
        CAN_TransmitterStatusChangeIntDisable(pCANx);
    }

    if (pCANConfig->sSetting.bWakeUpIEn)
    {
        CAN_WakeUpIntEn(pCANx);
        bTxIntEn = 1;
    }
    else
    {
        CAN_WakeUpIntDisable(pCANx);
    }

    if (pCANConfig->sSetting.bWakeUpEn)
    {
        CAN_WakeUpEn(pCANx);
    }
    else
    {
        CAN_WakeUpDisable(pCANx);
    }

    if (bTxIntEn)
    {
        // enable can tx interrupt
        NVIC_EnableIRQ(MSCAN_TX_IRQn);
    }

    if (pCANConfig->sSetting.bCanEn)
    {
        CAN_Enable(pCANx);
    }

}

/*----------------------------------------------------------------------------*/
/* Denitialize MSCAN module. */
uint8_t CAN_DeInit(MSCAN_Type *pCANx)
{
    UNUSED(pCANx);

    if (!CAN_LaunchInitialRequest(MSCAN))
    {
        return false;
    }

    CAN_Disable(MSCAN);
    SIM->SCGC &= ~SIM_SCGC_MSCAN_MASK;

    return true;
}

/*----------------------------------------------------------------------------*/
/* MSCAN enter into sleep mode. */
uint8_t CAN_EnterSleep(MSCAN_Type *pCANx)
{
    if (CAN_IsInitialMode(pCANx))
    {
        return false;
    }

    if (CAN_IsWakeUpIntFlag(pCANx))
    {
        //WUPIF is set, clear it
        CAN_ClearWUPIF_Flag(pCANx);
    }

    // enable wakeup interrupt
    CAN_WakeUpEn(pCANx);
    CAN_WakeUpIntEn(pCANx);

    // enter sleep mode
    CAN_SleepModeReq(pCANx);

    return true;
}

/*----------------------------------------------------------------------------*/
/* MSCAN wakeup from sleep mode. */
uint8_t CAN_WakeUpFromSleep(MSCAN_Type *pCANx)
{
    CAN_ClearSLPRQ_Flag(pCANx);
    while (CAN_IsSleepMode(pCANx))
    {

    }

    return true;
}

/*----------------------------------------------------------------------------*/
/* Launch CAN initialisation mode request. */
uint8_t CAN_LaunchInitialRequest(MSCAN_Type *pCANx)
{
    CAN_InitialModeReq(pCANx);
    while(!CAN_IsInitialMode(pCANx))
    {

    }

    return true;
}

/*----------------------------------------------------------------------------*/
/* Write a frame data to TX buffer. */
uint8_t CAN_LoadOneFrameToBuff(MSCAN_Type *pCANx,MSCAN_RegisterFramePtr pFrameBuff)
{
    uint8_t u8TransmitterEmptyFlag;

    //get the empty transmitter buffer
    u8TransmitterEmptyFlag = CAN_GetTransmitterBufferEmptyFlag(MSCAN);
    if (TRANSMITTER_TX_NO_EMPTY == u8TransmitterEmptyFlag)
    {
        return false;
    }

    // select transmitter buffer
    CAN_TxBuffSelect(pCANx,u8TransmitterEmptyFlag);

    //don't copy  time stamps, so here Sub 2 byter
    memcpy((void *)&pCANx->TEIDR0,(void *)pFrameBuff,sizeof(MSCAN_RegisterFrameType)-2);

    CAN_LaunchTransmitBuffer(pCANx,CAN_GetTxBuffSelect(pCANx));

    return true;
}

/*----------------------------------------------------------------------------*/
/* Read a frame data from RX buffer. */
uint8_t CAN_ReadOneFrameFromBuff(MSCAN_Type *pCANx,MSCAN_FramePtr pRxFrame)
{
    IDR1_3_UNION sIDR1;
    IDR1_3_UNION sIDR3;
    uint8_t i;

    if (CAN_IsRxBuffFull(pCANx))
    {
        sIDR1.Bytes = CAN_ReadIDR1Reg(pCANx);
        sIDR3.Bytes = CAN_ReadIDR3Reg(pCANx);
        pRxFrame->bIsExtOrStand = sIDR1.IDR1.R_TEIDE;
        pRxFrame->bIsRemoteFrame = sIDR3.IDR3.ERTR;
        pRxFrame->ID_Type.ExtID.EID28_21 = CAN_ReadIDR0Reg(pCANx);
        pRxFrame->ID_Type.ExtID.EID20_18 = sIDR1.IDR1.EID20_18_OR_SID2_0;
        pRxFrame->ID_Type.ExtID.EID17_15 = sIDR1.IDR1.EID17_15;
        pRxFrame->ID_Type.ExtID.EID14_7 = CAN_ReadIDR2Reg(pCANx);
        pRxFrame->ID_Type.ExtID.EID6_0 = sIDR3.IDR3.EID6_0;

        pRxFrame->DLR = pCANx->RDLR&0x0F;

        for (i = 0; i < pRxFrame->DLR; i++)
        {
            pRxFrame->DSR[i] = pCANx->REDSR[i];
        }

        // read stamps
        pRxFrame->u8TSRH = CAN_ReadTTSRHReg(pCANx);
        pRxFrame->u8TSRL = CAN_ReadTTSRLReg(pCANx);

        // clear receiver full flag
        CAN_ClearRXF_Flag(pCANx);
        return true;
    }

    // return data frame
    return false;
}

/*----------------------------------------------------------------------------*/
/* Set receive callback function for MSCAN. */
void MSCAN_SetRxCallBack(MSCAN_CallbackType pCallBack)
{
    MSCAN_RxCallback[0] = pCallBack;
}

/*----------------------------------------------------------------------------*/
/* Set transmit callback function for MSCAN. */
void MSCAN_SetTxCallBack(MSCAN_CallbackType pCallBack)
{
    MSCAN_TxCallback[0] = pCallBack;
}

/*----------------------------------------------------------------------------*/
/* MSCAN Receive interrupt service routine. */
void MSCAN_RX_IRQHandler(void)
{
    if (MSCAN_RxCallback[0])
    {
        MSCAN_RxCallback[0]();
    }
}

/*----------------------------------------------------------------------------*/
/* MSCAN transmitting interrupt service routine. */
void MSCAN_TX_IRQHandler(void)
{
    if (MSCAN_TxCallback[0])
    {
        MSCAN_TxCallback[0]();
    }
}

/** @} *//* end group */

