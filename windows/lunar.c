#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "lunar.h"

extern void parse_file(const char *);

HWND hwnd;
int running = 1;
int x = 50;

LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) {
        PostQuitMessage(0);
        running = 0;
    }
    return DefWindowProc(h, m, w, l);
}

void execute_commands(HDC hdc) {
    RECT r;
    GetClientRect(hwnd, &r);

    for (int i = 0; i < cmd_count; i++) {
        Command *c = &commands[i];

        if (c->type == CMD_CLEAR) {
            HBRUSH bg = CreateSolidBrush(RGB(0,0,0));
            FillRect(hdc, &r, bg);
            DeleteObject(bg);
        }

        else if (c->type == CMD_RECT) {
            HBRUSH b = CreateSolidBrush(RGB(200,0,255));
            RECT rc = { x, c->b, x + c->c, c->b + c->d };
            FillRect(hdc, &rc, b);
            DeleteObject(b);
        }

        else if (c->type == CMD_TEXT) {
            SetTextColor(hdc, RGB(255,255,255));
            SetBkMode(hdc, TRANSPARENT);
            TextOutA(hdc, c->a, c->b, c->text, lstrlenA(c->text));
        }

        else if (c->type == CMD_TITLE) {
            SetWindowTextA(hwnd, c->text);
        }

        else if (c->type == CMD_MOVE) {
            x += c->a;
        }
    }
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE, LPSTR, int) {
    parse_file(__argv[1] ? __argv[1] : "script.ln");

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = h;
    wc.lpszClassName = "LunarWin";
    RegisterClassA(&wc);

    hwnd = CreateWindowA(
        wc.lpszClassName, "Lunar Application",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        200,200,800,600,
        0,0,h,0
    );

    HDC hdc = GetDC(hwnd);
    MSG msg;

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
