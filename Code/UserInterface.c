#include "UserInterface.h"

#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "raylib_wrapper.h"

bool UserInterface_ShowHelp(void)
{
    const Rectangle windowBox = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    bool result = !GuiWindowBox(windowBox, "Help");

    return result;
}

bool UserInterface_ShowFolderTree(void)
{

}
