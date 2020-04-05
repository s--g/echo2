/**
 * echo2: border.c
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

#include "border.h"

/**
 * Outputs a horizontal border based on the selected border style
 *
 * @return void
 */
void outputHorizontalBorder()
{
    char *corner;
    char *horizontal;
    int i = 0;
    
    printSpaces();
    
    switch(state.borderStyle)
    {
        case BORDER_STYLE_1:
            corner = "+";
            horizontal = "-";
            break;
        
        case BORDER_STYLE_2:
            corner = "X";
            horizontal = "X";
            conWrite("\x1B[45m");
            break;
    }
    
    conWrite(corner);
    
    while(
        i++ < strlen(state.message) +
        (state.borderPaddingH * 2) +
        (state.characterSpacing * (strlen(state.message) - 1))
    )
    {
        conWrite(horizontal);
        
        if(state.textSpeed > 0)
            doSleep();
    }
    
    conWrite(corner);
    conWrite("\x1B[0m\n");
}

/**
 * Outputs a vertical border based on the selected border style
 *
 * @param int direction Specifies whether to output the left or right border
 * @return void
 */
void outputVerticalBorder(int direction)
{
    if(direction == BORDER_DIRECTION_RIGHT)
        outputBorderPadding();
    
    switch(state.borderStyle)
    {
        case BORDER_STYLE_1:
            conWrite("|");
            break;
        
        case BORDER_STYLE_2:
            conWrite("\x1B[45mX\x1B[0m");
            break;
    }
    
    if(direction == BORDER_DIRECTION_LEFT)
        outputBorderPadding();
}

/**
 * Outputs padding based on horizontal border padding attribute
 *
 * @return void
 */
void outputBorderPadding()
{
    int i;
    i = state.borderPaddingH;
    
    while(i-- > 0)
        conWrite(" ");
}
