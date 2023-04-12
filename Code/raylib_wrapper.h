#ifndef RAYLIB_WRAPPER_H
#define RAYLIB_WRAPPER_H

#if defined(__clang__)
// TODO
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC disgnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Walloc-size-larger-than="
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4996) // unsafe crt functions
#pragma warning(disable: 4244) // lossy implicit type conversion
#endif

#include "../raygui/raygui.h"

#if defined(__clang__)
// TODO
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif // RAYLIB_WRAPPER_H
