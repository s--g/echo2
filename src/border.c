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
    char corner;
    char horizontal;
    int i = 0;
    
    printSpaces();
    
    switch(state.borderStyle)
    {
        case BORDER_STYLE_1:
            corner = '+';
            horizontal = '-';
            break;
        
        case BORDER_STYLE_2:
            corner = 'X';
            horizontal = 'X';
            printf("%c[45m", 27);
            break;
    }
    
    putchar(corner);
    
    while(
        i++ < strlen(state.message) +
        (state.borderPaddingH * 2) +
        (state.characterSpacing * (strlen(state.message) - 1))
    )
        putchar(horizontal);
    
    printf("%c%c[0m\n", corner, 27);
}

/**
 * Outputs a horizontab border based on the selected border style
 *
 * @param int direction Specifies whether to output the left or right border
 * @return void
 */
void outputVerticalBorder(direction)
int direction;
{
    if(direction == BORDER_DIRECTION_RIGHT)
        outputBorderPadding();
    
    switch(state.borderStyle)
    {
        case BORDER_STYLE_1:
            putchar('|');
            break;
        
        case BORDER_STYLE_2:
            printf("%c[45mX%c[0m", 27, 27);
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
        putchar(' ');
}
