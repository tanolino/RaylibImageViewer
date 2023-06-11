#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

void Window_Init(void);
bool Window_ShouldClose(void);
void Window_ToggleFullscreen(void);
void Window_Close(void);

#endif // WINDOW_H