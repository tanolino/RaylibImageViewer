#include "UserInterface.h"

#include "Tree.h"

#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "raylib_wrapper.h"

bool UserInterface_ShowHelp(void)
{
    const Rectangle windowBox = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    bool result = !GuiWindowBox(windowBox, "Help");

    return result;
}

void UserInterface_ShowFolderTree(void)
{
    const Rectangle rect = { 0, 0, 100, 20 };
    GuiLabel(rect, Tree_GetCurrent());
}
