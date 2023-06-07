#include "Window.h"

#define RAYGUI_IMPLEMENTATION
#include <raylib.h>

typedef struct Vector2int {
    int width;
    int height;
} Vector2int;

const Vector2int minimal_window = { 400, 400 };
Vector2int fullscreen_return_pos = { 0 };
Vector2int fullscreen_return_size = { 400, 400 };

void Window_Init(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT);
    InitWindow(minimal_window.width, minimal_window.height, "raylib Hello!");
#if defined(PLATFORM_WEB)
#else
    SetTargetFPS(30);
    SetWindowMinSize(minimal_window.width, minimal_window.height);
#endif
}

bool Window_ShouldClose(void)
{
    return WindowShouldClose();
}

void Window_ToggleFullscreen(void)
{
    if (IsWindowState(FLAG_WINDOW_UNDECORATED))
    {
        SetWindowSize(fullscreen_return_size.width, fullscreen_return_size.height);
        SetWindowPosition(fullscreen_return_pos.width, fullscreen_return_pos.height);
        ClearWindowState(FLAG_WINDOW_UNDECORATED);
    }
    else
    {
        const Vector2 windowPos = GetWindowPosition();
        fullscreen_return_pos.width = (int)windowPos.x;
        fullscreen_return_pos.height = (int)windowPos.y;
        fullscreen_return_size.width = GetRenderWidth();
        fullscreen_return_size.height = GetRenderHeight();
        const int monitor = GetCurrentMonitor();
        const int newWidth = GetMonitorWidth(monitor);
        const int newHeight = GetMonitorHeight(monitor);
        SetWindowState(FLAG_WINDOW_UNDECORATED);
        SetWindowPosition(0, 0);
        SetWindowSize(newWidth, newHeight);
        // ToggleFullscreen();
    }
}

void Window_Close(void)
{
    CloseWindow();
}
