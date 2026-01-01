#pragma once

#define MAX_CMDS 256

// Commands
typedef enum {
    CMD_CLEAR,
    CMD_RECT,
    CMD_TEXT,
    CMD_MOVE,
    CMD_TITLE
} CmdType;

// Main types
typedef struct {
    CmdType type;
    int a, b, c, d;
    char text[64];
} Command;

// Externalize commands
extern Command commands[MAX_CMDS];
extern int cmd_count;
