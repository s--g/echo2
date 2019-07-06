/**
 * echo2: args.c
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

#include "args.h"

/**
 * Parses input from command line
 *
 * @param int argc Argument count
 * @param char*[] argv Argument vector
 * @return void
 */
void parseInput(argc, argv)
int argc;
char *argv[];
{
    int arg = 1;
    
    while(arg < argc)
    {
        if(argv[arg][0] == '-')
            processArg(argv[arg]);
        else
            strcpy(state.message, argv[arg]);
        
        arg++;
    }
}

/**
 * Processes a command line option
 *
 * @param char[] option The option string
 * @return void
 */
void processArg(option)
char option[15];
{
    char key = option[1];
    char val[15];
    int i;
    
    for(i = 0; i < strlen(option); i++)
        val[i] = option[i + 2]; 
    
    processArgVal(key, val);
}

/**
 * Processes command line option value(s)
 *
 * @param char key The option key
 * @param char *p The option value string
 * @return void
 */
void processArgVal(key, p)
char key;
char *p;
{
    char currentVal[15];
    int count = 0;
    int i = 0;
    
    /* p = &val[0]; */
    
    if(*p == EOS)
        setArg(key, NULL, NULL);
    
    while(1)
    {
        if(*p != ',' && *p != EOS)
        {
            currentVal[i++] = *p;
            currentVal[i] = EOS;
        }
        else
        {
            if(i > 0)
            {
                setArg(key, count++, currentVal);
                i = 0;
            }
            
            if(*p == EOS)
                break;
        }
        
        p++;
    }
}

/**
 * Sets the respective state variable based on the argument value
 *
 * @param char key The option key
 * @param int index The index of the provided option value
 * @param char[] val The option value
 * @return void
 */
void setArg(key, index, val)
char key;
int index;
char val[15];
{
    int i;
    
    switch(key)
    {
        case 'l':
            if(index == 0)
                state.linesBefore = atoi(val);
            else if(index == 1)
                state.linesAfter = atoi(val);
            break;
        
        case 's':
            if(index == 0)
                state.spaces = atoi(val);
            break;
        
        case 'e':
            state.clearScreen = TRUE;
            break;
        
        case 'p':
            if(index == 0)
                state.characterSpacing = atoi(val);
            break;
        
        case 'c':
            state.center = TRUE;
            break;
            
        case 'f':
        case 'b':
            i = atoi(val);
            
            if(i < 0 || i > 3)
                error("Invalid value for -%c", key);
            
            if(key == 'f')
                state.foreground = 30 + i;
            else
                state.background = 40 + i;
            break;
            
        case 't':
            if(strcmp(val, "b"))
                state.bold = TRUE;
            else if(strcmp(val, "i"))
                state.italic = TRUE;
            else if(strcmp(val, "u"))
                state.underline = TRUE;
            else
                error("Invalid value for -t");
            break;
        
        case 'o':
            i = atoi(val);
            if(index == 0)
            {
                if(i == BORDER_STYLE_1 || i == BORDER_STYLE_2)
                    state.borderStyle = i;
                else
                    error("Invalid border style value for -b");
            }
            else if(index == 1)
                state.borderPaddingH = i;
            else if(index == 2)
                state.borderPaddingV = i;
            
            break;
        
        case 'd':
            if(index == 0)
            {
                if(atoi(val) > 0 && atoi(val) <= 50)
                    state.textSpeed = atoi(val);
                else
                    error("Invalid value for option -d");
            }
            
            break;
        
        case 'x':
            state.flashScreen = TRUE;
            break;
        
        case 'r':
            state.requestor = TRUE; 
            break;
        
        case 'a':
            state.alert = TRUE;
            break;
        
        case 'h':
            help();
            return;
            break;
        
        default:
            error("Invalid option \"%c\"", key);
            break;
    }
}
