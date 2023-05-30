#include <raylib.h>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include <stdio.h> // printf

#include "TextureToScreen.h"
#include "UserInterface.h"
#include "Tree.h"

void MainLoop();
void HandleInput();

static Texture2D target = { 0 };
static bool showHelp = false;
static bool showTree = true;

int main(int argc, char** argv) {
    if (argc < 2)
    {
        printf("\nusage: %s <image_file>\n", argv[0]);
        return 1;
    }

    printf("\nStarting with image %s\n", argv[1]);
    // Init
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1200, 800, "raylib Hello!");
    
    Tree_RegisterStart(argv[1]);
    target = LoadTexture(argv[1]);
    if (target.mipmaps > 1)
        GenTextureMipmaps(&target);
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
    HandleInput();
    
    // Start Draw State
    BeginDrawing();
    ClearBackground(BLACK); 
    TextureToScreen(&target);
    if (showHelp)
        showHelp &= UserInterface_ShowHelp();
    else if (showTree)
        UserInterface_ShowFolderTree();

    EndDrawing();
}

void HandleInput() {
    int keyPressed;
    while ((keyPressed = GetKeyPressed()) != 0)
    {
        switch (keyPressed)
        {
            // UI State Changes
        case KEY_S:
            TextureToScreen_NextZoomMode();
            break;
        case KEY_TAB:
        case KEY_SPACE:
            showTree = !showTree;
            break;
        case KEY_F1:
            showHelp = !showHelp;
            break;
#ifndef PLATFORM_WEB
        case KEY_F:
        case KEY_F11:
            ToggleFullscreen();
            break;
#endif
            // Interacting with the UI
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
}

