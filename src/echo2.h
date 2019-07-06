/**
 * echo2: echo2.h
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

#ifndef EOS
#define EOS '\0'
#endif

#undef NULL
#define NULL 0

int main();
void error();
void render();
void renderLine();
void renderChar();
void printSpaces();
int getCenteringSpaces();
void renderCharSpacing();
void credits();
void info();
void help();
