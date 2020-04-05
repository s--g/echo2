/**
 * echo2: state.c
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

#define BORDER_STYLE_NONE 0
#define BORDER_STYLE_1 1
#define BORDER_STYLE_2 2
#define BORDER_DIRECTION_LEFT 0
#define BORDER_DIRECTION_RIGHT 1

/**
 * Represents program state
 */
struct State
{
    /**
     * @var int linesBefore The number of lines to print before the output
     */
    int linesBefore;
    
    /**
     * @var int linesAfter The number of lines to print after the output
     */
    int linesAfter;
    
    /**
     * @var int spaces The number of spaces to print before the output
     */
    int spaces;
    
    /**
     * @var int delay The delay (in miliseconds) between each character output
     */
    int delay;
    
    /**
     * @var int foreground Text (foreground) colour option
     */
    int foreground;
    
    /**
     * @var int background Background colour option
     */
    int background;
    
    /**
     * @var int borderStyle Border style option
     */
    int borderStyle;
    
    /**
     * @var int borderPaddingV The number of spaces to output between the border
     *                         and the left and right of the text output
     */
    int borderPaddingH;
    
    /**
     * @var int borderPaddingV The number of lines to output between the border
     *                         and before and after the text output
     */
    int borderPaddingV;
    
    /**
     * @var int characterSpacing Character spacing (n characters)
     */
    int characterSpacing;
    
    /**
     * @var int textSpeed Text output speed (1-50)
     */
    int textSpeed;
    
    /**
     * @var BOOL center Center the output
     */
    BOOL center;
    
    /**
     * @var BOOL clearScreen Clear screen
     */
    BOOL clearScreen;
    
    /**
     * @var BOOL flashScreen Flashes the screen
     */
    BOOL flashScreen;
    
    /**
     * @var BOOL requestor Display text in system requeter
     */
    BOOL requestor;
    
    /**
     * @var BOOL alert Display text in alert
     */
    BOOL alert;
    
    /**
     * @var BOOL help Display help
     */
    BOOL help;
    
    /**
     * @var char[] Text to output
     */
    char message[1000];
    
    /**
     * @var int A count of the number of html characters in the message string
     */
    int htmlCharCount;
} state;
