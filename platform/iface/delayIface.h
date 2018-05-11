/*
 * delayIface.h
 *
 *  Created on: 10 May 2018
 *      Author: Jiisuki
 */

#ifndef PLATFORM_IFACE_DELAYIFACE_H_
#define PLATFORM_IFACE_DELAYIFACE_H_

#include <stdint.h>

void Delay_us(const uint32_t time_us);
void Delay_ns(const uint32_t time_ns);

#endif /* PLATFORM_IFACE_DELAYIFACE_H_ */
