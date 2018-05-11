/*
 * flash.c
 *
 *  Created on: 10 May 2018
 *      Author: Jiisuki
 */

#include "flashIface.h"

#include <stdint.h>
#include <stdlib.h>

// TODO: Implement functions
uint8_t Flash_readByte(const uint32_t addr)
{
    return (0);
}

void Flash_readBlock(const uint32_t addr, const size_t size, uint8_t* const dest)
{

}

void Flash_seek(const uint32_t offset, const Flash_Mode_t mode)
{

}
