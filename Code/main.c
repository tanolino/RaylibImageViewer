#include "raylib.h"
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include <stdio.h>

// #define RAYGUI_IMPLEMENTATION
// #include <raylib.h>
// #include "raylib_wrapper.h"

#include "TextureToScreen.h"
#include "UserInterface.h"

void MainLoop();

static Texture2D target;
static bool showHelp = false;

int main(int argc, char** argv) {
    if (argc < 2)
    {
        printf("\nusage: %s <image_file>\n", argv[0]);
        return 1;
    }
    
    // Init
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1200, 800, "raylib Hello!");
    
    target = LoadTexture(argv[1]);
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
    UnloadTexture(target);
    CloseWindow();
    return 0;
}

void MainLoop() {
    int keyPressed;
    while((keyPressed = GetKeyPressed()) != 0)
    {
        switch (keyPressed)
        {
            case KEY_S:
                TextureToScreen_NextZoomMode();
                break;
#ifndef PLATFORM_WEB
            case KEY_F:
            case KEY_F11:
                ToggleFullscreen();
                break;
#endif
            case KEY_F1:
                showHelp = !showHelp;
                break;
            case KEY_LEFT:
                printf("Left\n");
                break;
            case KEY_RIGHT:
                printf("Right\n");
                break;
            case KEY_UP:
                printf("Up\n");
                break;
            case KEY_DOWN:
                printf("Down\n");
                break;
            default:
                printf("No action for %d\n", keyPressed);
                break;
        }
    }
    
    // Start Draw State
    BeginDrawing();
    ClearBackground(BLACK); 
    TextureToScreen(&target);
    if (showHelp)
        showHelp &= UserInterface_ShowHelp();

    EndDrawing();
}

