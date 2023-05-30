#include "Tree.h"

#include <stdlib.h>
#include <raylib.h>
#include <stdbool.h>

#include "StringUtils.h"

unsigned int selectedFileRoot = 0;
FilePathList filesRoot = { 0 };

void CleanUpPath(char* path);

// Externally used Functions //
void Tree_RegisterStart(const char* start)
{
    if (IsPathFile(start))
    {
        char *tmp = { 0 };
        StringDuplicate(&tmp, start, USHRT_MAX);
        CleanUpPath(tmp);
        filesRoot = LoadDirectoryFilesEx(GetDirectoryPath(tmp), NULL, true);

        for (unsigned int i = 0; i < filesRoot.count; ++i)
        {
            CleanUpPath(filesRoot.paths[i]);
            // printf("\t%s\n", filesRoot.paths[i]);
            // printf("strcmp\n\t%s\n\t%s\n\t= %d\n", tmp, filesRoot.paths[i], strcmp(tmp, filesRoot.paths[i]));
        }

        for (selectedFileRoot = 0; selectedFileRoot < filesRoot.count; ++selectedFileRoot)
        {
            if (strcmp(tmp, filesRoot.paths[selectedFileRoot]) < 0)
            {
                --selectedFileRoot;
                break;
            }
        }

        StringFree(&tmp);
    }
    else
    {
        selectedFileRoot = 0;
        filesRoot = LoadDirectoryFiles(start);
    }
    
}

void Tree_CleanUp()
{
    UnloadDirectoryFiles(filesRoot);
}


const char* Tree_GetCurrent()
{
    return filesRoot.paths[selectedFileRoot];
}

void Tree_Go_Next()
{
    selectedFileRoot = (selectedFileRoot + 1) % filesRoot.count;
}

void Tree_Go_Previous()
{
    if (selectedFileRoot)
        --selectedFileRoot;
    else
        selectedFileRoot = filesRoot.count - 1;
}


void CleanUpPath(char* path)
{
    const char* abort_mission = path + 0xFFFF;
    // might buffer overrun
    while (*path != '\0' && path < abort_mission)
    {
        if (*path == '\\')
            *path = '/';

        ++path;
    }
}
