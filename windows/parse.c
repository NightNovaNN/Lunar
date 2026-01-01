#include <stdio.h>
#include <string.h>
#include "lunar.h"

// Command storage
Command commands[MAX_CMDS];
int cmd_count = 0;

void parse_file(const char *file) {
    FILE *f = fopen(file, "r");
    if (!f) {
        printf("Could not open %s\n", file);
        return;
    }

    char line[128];

    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        if (strncmp(line, "clear", 5) == 0) {
            commands[cmd_count++] = (Command){ CMD_CLEAR };
        }

        // rect x y w h
        else if (strncmp(line, "rect", 4) == 0) {
            Command c = { CMD_RECT };
            sscanf(line, "rect %d %d %d %d", &c.a, &c.b, &c.c, &c.d);
            commands[cmd_count++] = c;
        }

        // text x y "string"
        else if (strncmp(line, "text", 4) == 0) {
            Command c = { CMD_TEXT };
            sscanf(line, "text %d %d %[^\n]", &c.a, &c.b, c.text);
            commands[cmd_count++] = c;
        }

        // move dx
        else if (strncmp(line, "move", 4) == 0) {
            Command c = { CMD_MOVE };
            sscanf(line, "move %d", &c.a);
            commands[cmd_count++] = c;
        }

        // title "string"
        else if (strncmp(line, "title", 5) == 0) {
            Command c = { CMD_TITLE };
            sscanf(line, "title %[^\n]", c.text);
            commands[cmd_count++] = c;
        }
    }

    fclose(f);
}
