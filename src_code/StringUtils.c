#include "StringUtils.h"
#include <stdlib.h>

// Duplicate a string and write it into the given pointer
bool StringDuplicate(char** destination, const char* source, size_t max)
{
    if (destination == 0)
        return false;

    *destination = 0;
    size_t str_size = strnlen_s(source, max);
    if (str_size == 0 || str_size == max)
        return false;

    *destination = malloc(sizeof(char) * (str_size + 1));
    if (!*destination)
        return false;

    *destination[str_size] = '\0';
    strcpy_s(*destination, str_size, source);

    return true;
}

