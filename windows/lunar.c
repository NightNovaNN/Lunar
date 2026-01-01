#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "lunar.h"

// From parse.c
extern void parse_file(const char *);

// Global variables
HWND hwnd;
int running = 1;
int x = 50;

// Window procedure
LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) {
        PostQuitMessage(0);
        running = 0;
    }
    return DefWindowProc(h, m, w, l);
}

void execute_commands(HDC hdc) {
    // Get client rect
    RECT r;
    GetClientRect(hwnd, &r);

    // Execute each cmd
    for (int i = 0; i < cmd_count; i++) {
        Command *c = &commands[i];

        // Clear screen
        if (c->type == CMD_CLEAR) {
            HBRUSH bg = CreateSolidBrush(RGB(0,0,0));
            // clear entire window
            FillRect(hdc, &r, bg);
            DeleteObject(bg);
        }

        // Draw rectangle
        else if (c->type == CMD_RECT) {
            HBRUSH b = CreateSolidBrush(RGB(200,0,255));
            // x of left, y of top, width, height
            RECT rc = { x, c->b, x + c->c, c->b + c->d };
            FillRect(hdc, &rc, b);
            DeleteObject(b);
        }

        // Draw Text
        else if (c->type == CMD_TEXT) {
            SetTextColor(hdc, RGB(255,255,255));
            SetBkMode(hdc, TRANSPARENT);
            // x, y, text, length
            TextOutA(hdc, c->a, c->b, c->text, lstrlenA(c->text));
        }

        // Set window title
        else if (c->type == CMD_TITLE) {
            // title text
            SetWindowTextA(hwnd, c->text);
        }

        // Move command
        else if (c->type == CMD_MOVE) {
            // move x by a
            x += c->a;
        }
    }
}

// Entry point
int WINAPI WinMain(HINSTANCE h, HINSTANCE, LPSTR, int) {
    parse_file(__argv[1] ? __argv[1] : "script.ln");

    // Register window class
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = h;
    wc.lpszClassName = "LunarWin";
    RegisterClassA(&wc);

    // Create window
    hwnd = CreateWindowA(
        wc.lpszClassName, "Lunar Application",  // title
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,       // style
        200,200,800,600,                        // x,y,w,h
        0,0,h,0                                 // parent, menu, instance, param
    );

    HDC hdc = GetDC(hwnd);
    MSG msg;

    // Main loop
    while (running) {
        while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        execute_commands(hdc);
        Sleep(16);
    }
    return 0;
}
