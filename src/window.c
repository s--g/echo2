/**
 * echo2: window.c
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

#include "window.h"

#define CON_READ_BUFFER 32
#define DEFAULT_WINDOW_WIDTH 60
#define BOUNDS_REPORT_MIN_LENGTH 10

/**
 * Returns the width of the current window, measured by number of characters (columns)
 *
 * @return int
 */
int getWindowColumns()
{
    char rbuf[CON_READ_BUFFER];
    int len, start, ind, rows, cols;
    
    conWrite("\x9b" "0 q");
    len = conRead(rbuf);    /* "\x9b" "1;1;33;77 r" */
    
    if (len < BOUNDS_REPORT_MIN_LENGTH || rbuf[len - 1] != 'r')
        return DEFAULT_WINDOW_WIDTH; /* Failed to read Window Bounds Report, returning default value. */
    
    start = 5;
    ind = start;
    while (rbuf[ind] != ';')
        ind++;
    rbuf[ind] = 0;
    rows = atoi(rbuf + start);
    
    ind++;
    start = ind;
    while (rbuf[ind] != ' ')
        ind++;
    rbuf[ind] = 0;
    cols = atoi(rbuf + start);
    
    return cols;
}
