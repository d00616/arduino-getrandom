/*
   random_nRF5.cpp - Getentropy for Arduino
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

#include "random_nRF5.h"
#include <Arduino.h>

GetrandomNRF5::GetrandomNRF5() {}

ssize_t GetrandomNRF5::getrandom(void *__buffer, size_t __length,
                                 unsigned int __flags) {
  // ignore flags at the moment
  (void)__flags;
  // cut length if > 256
  if (__length > 256)
    __length = 256;
  uint8_t *dst = (uint8_t *)__buffer;

  // Start random number generator
  startRNG();
  for (size_t i = 0; i < __length; i++) {
    dst[i] = readByte();
  }
  // halt random number generator
  stopRNG();

  return __length;
}

void GetrandomNRF5::startRNG(void) {
#ifdef NRF51
  NRF_RNG->POWER = 1;
#endif
  NRF_RNG->TASKS_START = 1;
  NRF_RNG->EVENTS_VALRDY = 0;
  NRF_RNG->CONFIG = RNG_CONFIG_DERCEN_Enabled << RNG_CONFIG_DERCEN_Pos;
}

void GetrandomNRF5::stopRNG(void) {
  NRF_RNG->TASKS_STOP = 1;
#ifdef NRF51
  NRF_RNG->POWER = 0;
#endif
}

char GetrandomNRF5::readByte() {
  char ret;
  while (NRF_RNG->EVENTS_VALRDY == 0) {
    yield();
  }
  ret = (char)NRF_RNG->VALUE;
  NRF_RNG->EVENTS_VALRDY = 0;
  return ret;
}
