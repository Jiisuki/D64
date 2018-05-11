/*
 * fifoIface.h
 *
 *  Created on: 9 May 2018
 *      Author: Jiisuki
 */

#ifndef PLATFORM_IFACE_FIFOIFACE_H_
#define PLATFORM_IFACE_FIFOIFACE_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t* buffer;
    uint8_t head;
    uint8_t tail;
    size_t numBytes;
} FIFO_t;

typedef enum
{
    FIFO_Result_Success,
    FIFO_Result_Failed,
} FIFO_Result_t;

FIFO_Result_t FIFO_init(FIFO_t* const fifo, uint8_t* const buffer, const size_t numBytes);
FIFO_Result_t FIFO_write(FIFO_t* const fifo, uint8_t byte);
FIFO_Result_t FIFO_read(FIFO_t* const fifo, uint8_t* byte);

#endif /* PLATFORM_IFACE_FIFOIFACE_H_ */
