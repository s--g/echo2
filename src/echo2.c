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
#include "console.c"
#include "window.c"
#include "sleep.c"
#include "border.c"

BOOL evenTick;

/**
 * Main entry point
 *
 * @param int argc Argument count
 * @param char*[] argv Argument vector
 * @return int
 */
int main(int argc, char *argv[])
{
    /* State initialization */
    state.borderStyle = BORDER_STYLE_NONE;
    state.borderPaddingH = 1;
    state.borderPaddingV = 0;
    state.characterSpacing = 0;
    state.textSpeed = 0;
    evenTick = TRUE;
    
    initConsole();
    parseInput(argc, argv);
    render();
    closeIntuition();
    closeConsole();
    exit(0);
}

/**
 * Displays error message and exits
 *
 * @param char* message The message to display
 * @param char* param Parameter to be included in message
 * @return void
 */
void error(char *message, char *param)
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
    closeConsole();
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
    i = 0;
    
    do
    {
        if(state.message[i] == '<')
            state.htmlCharCount += processTag(state.message, i) - i;
    } while(state.message[i++] != EOS);
    
    if(state.clearScreen)
        putchar(12);
    
    if(state.flashScreen)
        putchar(7);
    
    if(state.requestor)
    {
        displayRequester(state.message);
        return;
    }
    
    if(state.alert)
    {
        displayAlert(state.message);
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
void renderLine(BOOL renderMessage)
{
    int i;
    char temp[10];
    
    printSpaces();
    
    if(state.borderStyle != BORDER_STYLE_NONE)
        outputVerticalBorder(BORDER_DIRECTION_LEFT);
    
    if(state.foreground)
    {
        sprintf(temp, "\x1B[%dm", state.foreground);
        conWrite(temp);
    }
    
    if(state.background)
    {
        sprintf(temp, "\x1B[%dm", state.background);
        conWrite(temp);
    }
    
    i = 0;
    
    if(!renderMessage)
        i = state.htmlCharCount;
    
    while(state.message[i] != EOS)
    {
        if(renderMessage && state.message[i] == '<')
            i = processTag(state.message, i);
        
        renderChar(
            renderMessage?state.message[i]:' ',
            state.message[i + 1] == EOS,
            renderMessage
        );
        
        i++;
    }
    
    conWrite("\x1B[0m");
    
    if(state.borderStyle != BORDER_STYLE_NONE)
        outputVerticalBorder(BORDER_DIRECTION_RIGHT);
    
    conWrite("\n");
}

/**
 * Processes a HTML tag
 *
 * @param char* message The message string
 * @param int pos The current render position
 */
int processTag(char *message, int pos)
{
    BOOL enable;
    int p = pos + 1;
    
    if(message[p] == '/' && message[p + 2] == '>')
    {
        conWrite("\x1B[0m");
        return p + 3;
    }
    else if(message[p + 1] != '>')
        return pos;
    
    switch(message[p])
    {
        case 'b':
            conWrite("\x1B[1m");
            break;
        
        case 'i':
            conWrite("\x1B[3m");
            break;
        
        case 'u':
             conWrite("\x1B[4m");
            break;
        
        default:
            return p - 1;
    }
    
    return p + 2;
}

/**
 * Renders a single character and delays for text speed wait time
 *
 * @param char c Character to render
 * @param BOOL last Indicates if it is the last character
 * @param BOOL sleeping
 * @return void
 */
void renderChar(char c, BOOL last, BOOL sleeping)
{
    char ch[1];
    sprintf(ch, "%c", c);
    conWrite(ch); 
    
    if(!last)
        renderCharSpacing();
    
    if(sleeping)
        doSleep();
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
        {
            conWrite(" ");
            doSleep();
        }
    }
}

/**
 * Sleeps based on text speed
 *
 * @return void
 */
void doSleep()
{
    switch(state.textSpeed)
    {
        case -1:
            sleep(((rand() % 10) + 2) * ((rand() % 2) + 1));
            break;
        case 1:
        case 2:
            sleep(3 - state.textSpeed);
            break;
        
        case 3:
        case 4:
            if(evenTick)
            {
                sleep(5 - state.textSpeed);
                evenTick = FALSE;
            }
            else
                evenTick = TRUE;
            break;
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
        conWrite(" ");
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
    spaces -= ((strlen(state.message) - state.htmlCharCount) * (state.characterSpacing + 1)) / 2;
    
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
    printf("%c[1mecho2%c[0m v0.4 %c[4mhttp://echo2.org%c[0m ", 27, 27, 27, 27);
    printf("%c[3m(c)1991-2020 Steven George%c[0m\n", 27, 27);
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
    printf("  Supported HTML tags: <b>, <i>, <u>\n");
    printf("  -l<n,n>   n blank lines before and after text\n");
    printf("  -s<n>     n spaces before text\n");
    printf("  -p<n>     n character spacing\n");
    printf("  -c        Center text\n");
    printf("  -e        Clear screen first\n");
    printf("  -f<n>     Foreground color [0-3]\n");
    printf("  -b<n>     Background color [0-3]\n");
    printf("  -o<n,n,n> Border style [1-2], padding h, padding v\n");
    printf("  -d<n>     Text output speed [1-4]\n");
    printf("  -x        Flash screen\n");
    printf("  -r        Show text in requester\n");
    printf("  -a        Show text in alert\n");
    printf("  -h        Show this help\n");
}
