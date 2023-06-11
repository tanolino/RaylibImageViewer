#include "TextureToScreen.h"
#include "raylib.h"

#include <stdio.h>

void TextureToScreen_FitAll(const Texture2D* source)
{
    if (!source)
        return;
    if (!source->width || !source->height)
        return;

    const float sourceWidth = (float)source->width;
    const float sourceHeight = (float)source->height;
    const float screenWidth = (float)GetRenderWidth();
    const float screenHeight = (float)GetRenderHeight();
    const float scaleX = screenWidth / sourceWidth;
    const float scaleY = screenHeight / sourceHeight;

    Vector2 position = {0.f, 0.f};
    float scale;
    if (scaleY <= scaleX) {
        position.x = (screenWidth - sourceWidth * scaleY) / 2.f;
        scale = scaleY;
    } else {
        position.y = (screenHeight - sourceHeight * scaleX) / 2.f;
        scale = scaleX;
    }

    const float rotation = 0.f;

    DrawTextureEx(
        *source,
        position,
        rotation,
        scale,
        WHITE);
}

void TextureToScreen_ZoomFill(const Texture2D* source)
{
    if (!source)
        return;
    if (!source->width || !source->height)
        return;

    const float sourceWidth = (float)source->width;
    const float sourceHeight = (float)source->height;
    const float screenWidth = (float)GetRenderWidth();
    const float screenHeight = (float)GetRenderHeight();
    const float scaleX = screenWidth / sourceWidth;
    const float scaleY = screenHeight / sourceHeight;

    // printf("1 %d\t2 %d\n", GetScreenWidth(), GetRenderWidth());

    Rectangle srcRect = { 0.f, 0.f, sourceWidth, sourceHeight };
    Rectangle dstRect = { 0.f, 0.f, screenWidth, screenHeight };
    Vector2 origin = {0.f, 0.f};
    if (scaleY <= scaleX) {
        const float newHeight = screenHeight / scaleX;
        srcRect.y = (sourceHeight - newHeight) / 2.f;
        srcRect.height = newHeight;
    } else {
        const float newWidth = screenWidth / scaleY;
        srcRect.x = (sourceWidth - newWidth) / 2.f;
        srcRect.width = newWidth;
    }

    const float rotation = 0.f;

    DrawTexturePro(
        *source,
        srcRect,
        dstRect,
        origin,
        rotation,
        WHITE);
}

void TextureToScreen_ScrollContent(const Texture2D* source,
        double progress, double zoom)
{
    if (!source)
        return;

    // TODO
}

static ZoomMode_t CurrentZoomMode = ZM_FitAll;
void TextureToScreen_NextZoomMode(void)
{
    if (CurrentZoomMode == ZM_ZoomFill)
        CurrentZoomMode = ZM_FitAll;
    else
        CurrentZoomMode = CurrentZoomMode + 1;
}

void TextureToScreen(const Texture2D* source)
{
    switch (CurrentZoomMode)
    {
    case ZM_FitAll:
        TextureToScreen_FitAll(source);
        break;
    case ZM_ZoomFill:
        TextureToScreen_ZoomFill(source);
        break;
    default:
        fprintf(stderr, "Invalid ZoomMode_t, encountered: %d",
            CurrentZoomMode);
        CurrentZoomMode = ZM_FitAll;
        break;
    }
}

