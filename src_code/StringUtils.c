#include "StringUtils.h"
#include <stdlib.h> // malloc

// Duplicate a string and write it into the given pointer
bool StringDuplicate(char** destination, const char* source, size_t limit_length)
{
    if (destination == 0)
        return false;

    *destination = 0;
    size_t str_size =
#ifdef WIN32
    strnlen_s(source, limit_length);
#else
    strlen(source);
#endif
    if (str_size == 0 || str_size >= limit_length)
        return false;

    char* tmp = malloc(sizeof(char) * (str_size + 1));
    if (!tmp)
        return false;

#ifdef WIN32
    memcpy(tmp, source, sizeof(char) * str_size);
#else
    strcpy(tmp, source);
#endif
    tmp[str_size] = '\0';
    *destination = tmp;

    return true;
}

