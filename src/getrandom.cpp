/*
   random.cpp - Getentropy for Arduino
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

#include <getrandom.h>

// Global instance of the main class for sketches to use.
GetrandomType Getrandom;

ssize_t getrandom(void *__buffer, size_t __length, unsigned int __flags) {
  return Getrandom.getrandom(__buffer, __length, __flags);
}

int getentropy(void *buf, size_t buflen) {
  int ret;

  if (buflen > 256)
    goto failure;
  ret = getrandom(buf, buflen, 0);
  if (ret < 0)
    return ret;
  if ((size_t)ret == buflen)
    return 0;
failure:
  return -1;
}
