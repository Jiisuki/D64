/*
 * fifo.c
 *
 *  Created on: 9 May 2018
 *      Author: Jiisuki
 */

#include "fifoIface.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

FIFO_Result_t FIFO_init(FIFO_t* const fifo, uint8_t* const buffer, const size_t numBytes)
{
    assert(fifo);
    assert(buffer);

    fifo->buffer = buffer;
    fifo->numBytes = numBytes;
    fifo->head = 0;
    fifo->tail = 0;

    return (FIFO_Result_Success);
}

FIFO_Result_t FIFO_write(FIFO_t* const fifo, uint8_t byte)
{
    assert(fifo);

    fifo->buffer[fifo->head] = byte;
    fifo->head = (fifo->head + 1) % fifo->numBytes;

    return (FIFO_Result_Success);
}

FIFO_Result_t FIFO_read(FIFO_t* const fifo, uint8_t* byte)
{
    assert(fifo);

    *byte = fifo->buffer[fifo->tail];
    fifo->tail = (fifo->tail + 1) % fifo->numBytes;

    return (FIFO_Result_Success);
}
