/*
   random_nRF5.h - Getentropy for Arduino
   Original Copyright (c) 2017 Frank Holtz.  All right reserved.

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

#pragma once

#include <Arduino.h>
#include <stdio.h> // for size_t
//#include <errno.h> // include if available

#ifdef __RFduino__
#include <chip.h>
#else
#include <nrf.h>
#endif

#include "random_nRF5.h"

class GetrandomNRF5 {
public:
  GetrandomNRF5();
  ssize_t getrandom(void *__buffer, size_t __length, unsigned int __flags);

private:
  void startRNG(void);
  void stopRNG(void);
  char readByte();
};
