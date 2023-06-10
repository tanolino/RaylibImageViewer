#include "ImageLoader.h"
// #include <raylib.h>
#include <external/stb_image.h>
#include <stdio.h>

static struct
{
    Image     image;
    Texture2D texture;
    struct
    {
        int   Count;
        int   Current;
        int   FrameOffset;
        float AccumFrameTime;
        int*  Delays;
    } animation;
} loaderState = { 0 };

static void ImageLoader_Internal_Load(const char* imageFile)
{
    Image newImage = { 0 };
    if (!imageFile)
    {
        loaderState.image = newImage;
        return;
    }
    else if (IsFileExtension(imageFile, ".gif"))
    {
        unsigned int dataSize = 0;
        unsigned char* fileData = LoadFileData(imageFile, &dataSize);
        if (fileData)
        {
            int comp = 0;
            newImage.data = stbi_load_gif_from_memory(fileData, dataSize,
                &loaderState.animation.Delays,
                &newImage.width, &newImage.height,
                &loaderState.animation.Count, &comp, 4);
            newImage.mipmaps = 1;
            newImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

            free(fileData);
        }
    }
    else
    {
        newImage = LoadImage(imageFile);
        loaderState.animation.Count = 0;
    } 
    loaderState.image = newImage;
    
    loaderState.texture = LoadTextureFromImage(loaderState.image);
    if (loaderState.texture.mipmaps > 1)
        GenTextureMipmaps(&loaderState.texture);
    loaderState.animation.Current = 0;
    loaderState.animation.FrameOffset = 4 *
        loaderState.image.width * loaderState.image.height;
}

static void ImageLoader_Internal_Unload()
{
    UnloadTexture(loaderState.texture);
    UnloadImage(loaderState.image);
    if (loaderState.animation.Delays)
    {
        free(loaderState.animation.Delays);
        loaderState.animation.Delays = 0;
    }
}

void ImageLoader_Init(const char* imageFile)
{
    ImageLoader_Internal_Load(imageFile);
}

void ImageLoader_CleanUp(void)
{
    ImageLoader_Internal_Unload();
}

void ImageLoader_UpdateImage(const char* imageFile)
{
    ImageLoader_Internal_Unload();
    ImageLoader_Internal_Load(imageFile);
}

void ImageLoader_UpdateAnimation(float frameTime)
{
    if (loaderState.animation.Count <= 1)
        return; // we only have one frame

    loaderState.animation.AccumFrameTime += frameTime * 1000.0f;
    const int currentDelay = loaderState.animation.Delays[loaderState.animation.Current];
    if (loaderState.animation.AccumFrameTime < currentDelay)
        return; // do not update yet

    loaderState.animation.AccumFrameTime -= currentDelay;
    loaderState.animation.Current += 1;
    loaderState.animation.Current %= loaderState.animation.Count;
    const int offset = loaderState.animation.FrameOffset * loaderState.animation.Current;
    UpdateTexture(loaderState.texture, (char*)loaderState.image.data + offset);
}

const Texture2D* ImageLoader_GetTexture(void)
{
    return &loaderState.texture;
}
