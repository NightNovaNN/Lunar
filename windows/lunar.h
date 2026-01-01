#pragma once

#define MAX_CMDS 256

typedef enum {
    CMD_CLEAR,
    CMD_RECT,
    CMD_TEXT,
    CMD_MOVE,
    CMD_TITLE
} CmdType;

typedef struct {
    CmdType type;
    int a, b, c, d;
    char text[64];
} Command;

extern Command commands[MAX_CMDS];
extern int cmd_count;
