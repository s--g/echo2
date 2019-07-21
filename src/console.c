/**
 * echo2: console.c
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

#include "console.h"

#include <exec/types.h>
#include <exec/ports.h>

#include <libraries/dos.h>
#include <libraries/dosextens.h>

#include <stdlib.h>

#define CON_READ_BUFFER 32

static struct MsgPort *mp;
static struct StandardPacket sp;
static struct FileHandle *con;

/**
 * Initializes the console
 * 
 * @return void
 */
void initConsole()
{
    mp = (struct MsgPort *)CreatePort(NULL, 0);
    con = (struct FileHandle *)BADDR(((struct Process *)FindTask(NULL))->pr_CIS);
    setScreenMode(DOSTRUE);
}

/**
 * Close the console
 *
 * @return void
 */
void closeConsole()
{
    setScreenMode(DOSFALSE);
    DeletePort(mp);
}
 
/**
 * Set console screen mode
 *
 * @param LONG mode
 * @return LONG
 */
LONG setScreenMode(LONG mode)
{
    return putConSp(mp, &sp, ACTION_SCREEN_MODE, mode, 0, 0);
}

/**
 * Write message to console
 *
 * @param char* message
 * @return LONG
 */
LONG conWrite(char *message)
{
    return putConSp(mp, &sp, ACTION_WRITE, con->fh_Arg1, (LONG)message, strlen(message));
}

/**
 * Read message from console
 *
 * @param char* message
 * @return LONG
 */
LONG conRead(char *message)
{
    return putConSp(mp, &sp, ACTION_READ, con->fh_Arg1, (LONG)message, CON_READ_BUFFER);
}

/**
 * Put a StandardPacket to the console
 *
 * @param struct MsgPort* replyPort
 * @param struct StandardPacket* sp
 * @param LONG action
 * @param LONG arg1
 * @param LONG arg2
 * @param LONG arg3
 * @return LONG
 */
LONG putConSp(struct MsgPort *replyPort, struct StandardPacket *sp, LONG action, LONG arg1, LONG arg2, LONG arg3)
{
    sp->sp_Msg.mn_Node.ln_Type = NT_MESSAGE;
    sp->sp_Msg.mn_Node.ln_Pri = 0;
    sp->sp_Msg.mn_Node.ln_Name = (char *)&(sp->sp_Pkt);
    sp->sp_Msg.mn_Length = sizeof(struct StandardPacket);
    sp->sp_Msg.mn_ReplyPort = replyPort;
    
    sp->sp_Pkt.dp_Link = &(sp->sp_Msg);
    sp->sp_Pkt.dp_Port = replyPort;
    sp->sp_Pkt.dp_Type = action;
    sp->sp_Pkt.dp_Arg1 = arg1;
    sp->sp_Pkt.dp_Arg2 = arg2;
    sp->sp_Pkt.dp_Arg3 = arg3;
    
    PutMsg(con->fh_Type, &(sp->sp_Msg));
    
    Wait(1L << mp->mp_SigBit);
    GetMsg(mp);
    return sp->sp_Pkt.dp_Res1; 
}
