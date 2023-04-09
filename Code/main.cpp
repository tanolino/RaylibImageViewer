#include <iostream>
#include <memory>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define RAYGUI_IMPLEMENTATION
extern "C" {
#include <raylib.h>
#include "../raygui/raygui.h"
}
using namespace std;

void MainLoop();
RenderTexture2D target;

constexpr const unsigned int RenderWidth = 800;
constexpr const unsigned int RenderHeight = 600;

int main() {
    // Init
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1200, 800, "raylib Hello!");
    target = LoadRenderTexture(RenderWidth, RenderHeight);
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(MainLoop, 60, 1);
#else
    SetTargetFPS(30);
    SetWindowMinSize(400, 300);
    // Loop
    while (!WindowShouldClose()) {
        MainLoop();
    }
#endif
    // Cleanup
    CloseWindow();
    return 0;
}

void MainLoop() {
    float frameTime = GetFrameTime();
    
    BeginTextureMode(target);
	// Draw what you want to the target
	ClearBackground(WHITE);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
#if defined(PLATFORM_WEB)
    const int offset = 0;
#else
    const int offset = -RenderHeight;
#endif
    float scaleX = (float)GetScreenWidth() / (float)RenderWidth;
    float scaleY = (float)GetScreenHeight() / (float)RenderHeight;
    float offsetX = 0.f;
    float offsetY = 0.f;
    float scale = 1.f;
    if (scaleY <= scaleX) {
        offsetX = (float)RenderWidth * (scaleY - scaleX) / -2.f;
        scale = scaleY;
    } else {
        offsetY = (float)RenderHeight * (scaleX - scaleY) / -2.f;
        scale = scaleX;
    }
    DrawTexturePro(
        target.texture,
        Rectangle{0, offset, (float)RenderWidth, (float)-RenderHeight},
        Rectangle{offsetX, offsetY, (float)RenderWidth * scale,
                  (float)RenderHeight * scale},
        Vector2{0, 0}, 0, WHITE);

    GuiWindowBox(Rectangle{ 0, 0, GetScreenWidth() / 4, GetScreenHeight() }, "#198# PORTABLE WINDOW");
    EndDrawing();
}
