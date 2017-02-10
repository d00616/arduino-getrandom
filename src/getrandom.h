/*
   random_nRF5.h - Getentropy for Arduino
   Copyright (C) 2016-2017 Free Software Foundation, Inc. (GNU C Library)
   Copyright (c) 2017 Frank Holtz.  All right reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _RANDOM_H
#define _RANDOM_H 1

#include <Arduino.h>

/* Flags for use with getrandom.  */
#define GRND_NONBLOCK 0x01
#define GRND_RANDOM 0x02

/* Write LENGTH bytes of randomness starting at BUFFER.  Return the
   number of bytes written, or -1 on error.  */
ssize_t getrandom(void *__buffer, size_t __length, unsigned int __flags);

/* OpenBSD compatible getentropy */
int getentropy(void *buf, size_t buflen);

/* Include hardware specific implementation */
#if defined(__RFduino__) or defined(ARDUINO_ARCH_NRF5) or                      \
    defined(ARDUINO_ARCH_NRF51822) or defined(ARDUINO_ARCH_NRF51822) or        \
    defined(ARDUINO_ARCH_NRF52832)
// Nordic NRF5 series
#include "drivers/random_nRF5.h"
typedef GetrandomNRF5 GetrandomType;
#endif

extern GetrandomType Getrandom;

/* Errors if no errno.h available */
#ifndef EINVAL
#define EINVAL (int)(-15250)
#endif

#ifndef EFAULT
#define EFAULT (int)(-15251)
#endif

#ifndef EINTR
#define EINTR (int)(-15252)
#endif

#ifndef EINVAL
#define EINVAL (int)(-15253)
#endif

#endif /* _RANDOM_H */
