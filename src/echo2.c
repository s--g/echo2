/**
 * echo2: echo2.c
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

#include <stdio.h>
#include <exec/types.h>

#include "echo2.h"
#include "state.c"
#include "args.c"
#include "intuition.c"
#include "border.c"
#include "window.c"
#include "sleep.c"

/**
 * Main entry point
 *
 * @param int argc Argument count
 * @param char*[] argv Argument vector
 * @return int
 */
int main(argc,argv)
int argc;
char *argv[];
{
    /* State initialization */
    state.borderStyle = BORDER_STYLE_NONE;
    state.borderPaddingH = 1;
    state.borderPaddingV = 0;
    state.characterSpacing = 0;
    state.textSpeed = 50;
    
    parseInput(argc, argv);
    render();
    closeIntuition();
    exit(0);
}

/**
 * Displays error message and exits
 *
 * @param char[] message The message to display
 * @param char[] param Parameter to be included in message
 * @return void
 */
void error(message, param)
char message[100];
char param[100];
{
    printf("%c[0mERROR: ", 27);
    
    if(param == NULL)
        printf("%s\n", message);
    else
    {
        printf(message, param);
        printf("\n");
    }
    
    info();
    closeIntuition();
    exit(1);
}

/**
 * Performs main output
 * 
 * @return void
 */
void render()
{
    int i;
    
    if(state.clearScreen)
        putchar(12);
    
    if(state.flashScreen)
        putchar(7);
    
    if(state.requestor)
    {
        displayRequester(&state.message);
        return;
    }
    
    if(state.alert)
    {
        displayAlert(&state.message);
        return;
    }
    
    while(state.linesBefore-- > 0)
        printf("\n");
    
    if(state.center)
        state.spaces = getCenteringSpaces();
    
    if(state.borderStyle != BORDER_STYLE_NONE)
        outputHorizontalBorder();
    
    if(state.borderPaddingV > 0)
    {
        for(i = 0; i < state.borderPaddingV; i++)
            renderLine(FALSE);
    }
    
    renderLine(TRUE);
    
    if(state.borderPaddingV > 0)
    {
        for(i = 0; i < state.borderPaddingV; i++)
            renderLine(FALSE);
    }
    
    if(state.borderStyle != BORDER_STYLE_NONE)
        outputHorizontalBorder();
    
    while(state.linesAfter-- > 0)
        printf("\n");
}

/**
 * Renders a line of output
 * 
 * @param BOOL renderMessage If true renders the message in the state, otherwise renders spaces
 * @return void
 */
void renderLine(renderMessage)
BOOL renderMessage;
{
    int i;
    
    printSpaces();
    
    if(state.borderStyle != BORDER_STYLE_NONE)
        outputVerticalBorder(BORDER_DIRECTION_LEFT);
    
    if(state.foreground)
        printf("%c[%dm", 27, state.foreground);
    
    if(state.background)
        printf("%c[%dm", 27, state.background);
    
    if(state.italic)
        printf("%c[1m", 27);
    
    if(state.bold)
        printf("%c[3m", 27);
    
    if(state.underline)
        printf("%c[4m", 27);
    
    i = 0;
    while(state.message[i] != EOS)
    {
        renderChar(
            renderMessage?state.message[i]:' ',
            state.message[i + 1] == EOS
        );
        
        i++;
    }
    
    printf("%c[0m", 27);
    
    if(state.borderStyle != BORDER_STYLE_NONE)
        outputVerticalBorder(BORDER_DIRECTION_RIGHT);
    
    printf("\n");
}

/**
 * Renders a single character and delays for text speed wait time
 *
 * @param char c
 * @return void
 */
void renderChar(c, last)
char c;
BOOL last;
{
    putchar(c);
    
    if(!last)
        renderCharSpacing();
    
    sleep(50 - state.textSpeed);
}

/**
 * Renders character spacing
 *
 * @return void
 */
void renderCharSpacing()
{
    int i;
    
    if(state.characterSpacing > 0)
    {
        for(i = state.characterSpacing; i > 0; i--)
            putchar(' ');
    }
}

/**
 * Prints spaces in accordance with state.spaces
 *
 * @return void
 */
void printSpaces()
{
    int i = 0;
    
    while(i++ < state.spaces)
        putchar(' ');
}

/**
 * Gets the number of spaces required on the left hand side to center the output
 *
 * @return int
 */
int getCenteringSpaces()
{
    int spaces;
    spaces = getWindowColumns() / 2;
    spaces -= (strlen(state.message) * (state.characterSpacing + 1)) / 2;
    
    if(state.borderStyle != BORDER_STYLE_NONE)
        spaces -= (state.borderPaddingH / 2) + 2;
    
    return spaces;
}

/**
 * Output credits
 *
 * @return void
 */
void credits()
{
    printf("%c[1mecho2%c[0m v0.10 %c[4mhttp://echo2.org%c[0m ", 27, 27, 27, 27);
    printf("%c[3m(c)1992-2019 Steven George%c[0m\n", 27, 27);
}

/**
 * Output info
 *
 * @return void
 */
void info()
{
    credits();
    printf("Use -h for help\n");
}

/**
 * Output help
 *
 * @return void
 */
void help()
{
    credits();
    printf("\nUsage: echo2 [<options>] \"Your text\"\n");
    printf("  -l<n,n>   n blank lines before and after text\n");
    printf("  -s<n>     n spaces before text\n");
    printf("  -p<n>     n character spacing\n");
    printf("  -c        Center text\n");
    printf("  -e        Clear screen first\n");
    printf("  -f<n>     Foreground color [0-3]\n");
    printf("  -b<n>     Background color [0-3]\n");
    printf("  -t<b,i,u> Font style [b]old, [i]talic, [u]nderline\n");
    printf("  -o<n,n,n> Border style [1-2], padding l/r, t/b\n");
 /* printf("  -d<n>     Text output speed (milseconds)\n"); */
    printf("  -x        Flash screen\n");
    printf("  -r        Show text in requester\n");
    printf("  -a        Show text in alert\n");
    printf("  -h        Show this help\n");
}
