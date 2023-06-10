#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdbool.h>

bool StringDuplicate(char** destination, const char* source, size_t limit_length);
void StringFree(char** str_ptr);