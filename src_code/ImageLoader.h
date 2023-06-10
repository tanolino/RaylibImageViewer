#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <raylib.h>

void             ImageLoader_Init(const char* imageFile);
void             ImageLoader_CleanUp(void);
void             ImageLoader_UpdateImage(const char* imageFile);
void             ImageLoader_UpdateAnimation(float frameTime);
const Texture2D* ImageLoader_GetTexture(void);

#endif // IMAGE_LOADER_H