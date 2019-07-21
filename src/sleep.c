/**
 * echo2: sleep.c
 *
 * Copyright (C) 1992-2019 Steven George (echo2.org)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "sleep.h"

/**
 * Sleeps for given number of ticks (50 per second)
 *
 * @param int ticks
 * @see http://amigadev.elowar.com/read/ADCD_2.1/Includes_and_Autodocs_2._guide/node0292.html
 */
void sleep(int ticks)
{
    Delay(ticks);
}
