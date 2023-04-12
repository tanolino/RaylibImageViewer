#ifndef TEXTURE_TO_SCREEN_H
#define TEXTURE_TO_SCREEN_H

#define RAYGUI_IMPLEMENTATION
#include <raylib.h>

void TextureToScreen_FitAll(const Texture2D* source);
void TextureToScreen_ZoomFill(const Texture2D* source);
void TextureToScreen_ScrollContent(const Texture2D* source,
        double progress, double zoom);

typedef enum
{
    ZM_FitAll,
    ZM_ZoomFill
} ZoomMode_t;

void TextureToScreen_NextZoomMode(void);
void TextureToScreen(const Texture2D* source);

#endif // TEXTURE_TO_SCREEN_H
