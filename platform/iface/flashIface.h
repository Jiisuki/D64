/*
 * flashIface.h
 *
 *  Created on: 10 May 2018
 *      Author: Jiisuki
 */

#ifndef PLATFORM_IFACE_FLASHIFACE_H_
#define PLATFORM_IFACE_FLASHIFACE_H_

#include <stdint.h>
#include <stdlib.h>

typedef enum
{
    Flash_Mode_Read,
    Flash_Mode_Write,
} Flash_Mode_t;

uint8_t Flash_readByte(const uint32_t addr);
void Flash_readBlock(const uint32_t addr, const size_t size, uint8_t* const dest);
void Flash_seek(const uint32_t offset, const Flash_Mode_t mode);

#endif /* PLATFORM_IFACE_FLASHIFACE_H_ */
