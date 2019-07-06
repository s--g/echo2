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

#include <exec/types.h>
#include <exec/ports.h>

#include <libraries/dos.h>
#include <libraries/dosextens.h>

#include <stdlib.h>

static struct MsgPort *mp;
static struct StandardPacket sp;
static struct FileHandle *con;

void putConSp(struct MsgPort *replyPort, struct StandardPacket *sp, LONG action, LONG arg1, LONG arg2, LONG arg3)
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
}

LONG setScreenMode(LONG mode)
{
    putConSp(mp, &sp, ACTION_SCREEN_MODE, mode, 0, 0);
    Wait(1L << mp->mp_SigBit);
    GetMsg(mp);
    return sp.sp_Pkt.dp_Res1;
}

LONG conWrite(char *s, int length)
{
    putConSp(mp, &sp, ACTION_WRITE, con->fh_Arg1, (LONG)s, length);
    Wait(1L << mp->mp_SigBit);
    GetMsg(mp);
    return sp.sp_Pkt.dp_Res1;
}

LONG conRead(char *s, int length)
{
    putConSp(mp, &sp, ACTION_READ, con->fh_Arg1, (LONG)s, length);
    Wait(1L << mp->mp_SigBit);
    GetMsg(mp);
    return sp.sp_Pkt.dp_Res1;
}

/**
 * Returns the width of the current window, measured by number of characters (columns)
 *
 * @return int
 */
int getWindowColumns()
{
    char rbuf[32];
    int len, start, ind, rows, cols;

    mp = (struct MsgPort *)CreatePort(NULL, 0);
    con = (struct FileHandle *)BADDR(((struct Process *)FindTask(NULL))->pr_CIS);

    setScreenMode(DOSTRUE);
    conWrite("\x9b" "0 q", 4);
    len = conRead(rbuf, 32);    /* "\x9b" "1;1;33;77 r" */
    setScreenMode(DOSFALSE);
    DeletePort(mp);

    if (len < 10 || rbuf[len - 1] != 'r')
        return 60; /* Failed to read Window Bounds Report, returning default value. */

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
