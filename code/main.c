#include <raylib.h>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include <stdio.h> // printf

#include "StringUtils.h"
#include "TextureToScreen.h"
#include "UserInterface.h"
#include "Tree.h"
#include "Window.h"
#include "ImageLoader.h"

void MainLoop();
void HandleInput();
bool IsAskingForHelp(const char* param);
static bool showHelp = false;
static bool showTree = true;


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("\nStarting with working directory\n");
        Tree_RegisterStart(GetWorkingDirectory());
    }
    else if (IsAskingForHelp(argv[1]))
    {
        printf("\nusage: %s <image_file>|<image_folder>\n", argv[0]);
        return 0;
    }
    else
    {
        printf("Start with image: %s\n", argv[1]);
        Tree_RegisterStart(argv[1]);
    }

    Window_Init();
    ImageLoader_Init(Tree_GetCurrent());

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(MainLoop, 60, 1);
#else
    while (!Window_ShouldClose()) {
        MainLoop();
    }
#endif
    // Cleanup
    ImageLoader_CleanUp();
    Window_Close();
    Tree_CleanUp();

    return 0;
}

void MainLoop() {
    HandleInput();
    ImageLoader_UpdateAnimation(GetFrameTime());
    
    // Start Draw State
    BeginDrawing();
    ClearBackground(BLACK); 
    TextureToScreen(ImageLoader_GetTexture());
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
            Window_ToggleFullscreen();
            break;
#endif
            // Interacting with the UI
        case KEY_LEFT:
            printf("Left\n");
            Tree_Go_Previous();
            ImageLoader_UpdateImage(Tree_GetCurrent());
            break;
        case KEY_RIGHT:
            printf("Right\n");
            Tree_Go_Next();
            ImageLoader_UpdateImage(Tree_GetCurrent());
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

bool IsAskingForHelp(const char* param)
{
    if (param == 0)
        return false;

    return strcmp(param, "-?") == 0
        || strcmp(param, "-help") == 0
        || strcmp(param, "--?") == 0
        || strcmp(param, "--help") == 0;
}
