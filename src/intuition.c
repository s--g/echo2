/**
 * echo2: intuition.c
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

#include <intuition/intuition.h>
#include "intuition.h"

struct Window *Window = NULL;
struct IntuitionBase *IntuitionBase;

struct AlertMessage
{
   SHORT LeftEdge;
   BYTE TopEdge;
   char AlertText[50];
   BYTE Flag;
};

/**
 * Opens the intuition library
 * 
 * @return void
 */
void openIntution()
{
    void *OpenLibrary();
    
    if(!(IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 0L)))
       error("Can't open intuition library", NULL);
}

/**
 * Closes the intuition library if it has been opened
 *
 * @return void
 */
void closeIntuition()
{
    if(IntuitionBase)
        CloseLibrary(IntuitionBase);
}

/**
 * Displays text in a system alert
 *
 * @param char* text
 * @return void
 */
void displayRequester(char *text)
{
    struct IntuiText message;
    struct IntuiText okButton;
    
    message.FrontPen = 0;
    message.BackPen = 1;
    message.DrawMode = JAM2;
    message.LeftEdge = 10;
    message.TopEdge = 10;
    message.ITextFont = NULL;
    strcpy(message.IText, text);
    message.NextText = NULL;
    
    okButton.FrontPen = 0;
    okButton.BackPen = 1;
    okButton.DrawMode = JAM2;
    okButton.LeftEdge = 5;
    okButton.TopEdge = 4;
    okButton.ITextFont = NULL;
    okButton.IText = (UBYTE *)" Ok ";
    okButton.NextText = NULL;
    
    openIntution();
    AutoRequest(Window, &message, NULL, &okButton, 0L, 0L, 320L, 70L);
}

/**
 * Displays text in a system alert
 *
 * @param char* text
 * @return void
 */
void displayAlert(char *text)
{
    struct AlertMessage alert;
    alert.LeftEdge = 10;
    alert.TopEdge = 26;
    strcpy(alert.AlertText, text);
    alert.Flag = END;
    
    openIntution();
    DisplayAlert(RECOVERY_ALERT, &alert, 50L);
    return;
}
