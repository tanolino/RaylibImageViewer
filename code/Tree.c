#include "Tree.h"

#include <stdlib.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#ifndef _WIN32
#include <limits.h>
#endif

#include "StringUtils.h"

unsigned int selectedFileRoot = 0;
FilePathList filesRoot = { 0 };

static void CleanUpPath(char* path);
static void Go_Offset_OrDieTrying(int offset); // only 1 or -1
static bool SupportedFileFormat(const char* path);

// Externally used Functions //
void Tree_RegisterStart(const char* start)
{
    unsigned int result_id = 0;
    FilePathList result = { 0 };
    if (!start)
    {
        printf("We want to Start on an empty string ?\n");
    }
    else if (IsPathFile(start))
    {
        printf("Starting on file: %s\n", start);
        char *tmp = { 0 };
        StringDuplicate(&tmp, start, USHRT_MAX);
        CleanUpPath(tmp);
        const char* directory = GetDirectoryPath(tmp);
        printf("Loading GetDirectoryPath(%s) = %s\n", tmp, directory);
        result = LoadDirectoryFilesEx(directory, NULL, true);

        for (unsigned int i = 0; i < result.count; ++i)
        {
            CleanUpPath(result.paths[i]);
            // printf("\t%s\n", filesRoot.paths[i]);
            // printf("strcmp\n\t%s\n\t%s\n\t= %d\n", tmp, filesRoot.paths[i], strcmp(tmp, filesRoot.paths[i]));
        }

        if (result.count <= 1)
            goto CleanUpString;

        int minDist = abs(strcmp(tmp, result.paths[selectedFileRoot]));
        selectedFileRoot = 0;
        printf("Closest : %s\n", result.paths[0]);
        for (unsigned int i = 1; i < result.count; ++i)
        {
            const int dist = abs(strcmp(tmp, result.paths[i]));
            if (dist < minDist)
            {
                result_id = i;
                minDist = dist;
                printf("Closest (%d): %s\n", dist, result.paths[i]);
            }
        }
        
        CleanUpString:
        StringFree(&tmp);
    }
    else
    {
        printf("Start on directory: %s\n", start);
        result_id = 0;
        result = LoadDirectoryFiles(start);
    }
    selectedFileRoot = result_id;
    filesRoot = result;
}

void Tree_CleanUp(void)
{
    UnloadDirectoryFiles(filesRoot);
}


const char* Tree_GetCurrent(void)
{
    if (selectedFileRoot < filesRoot.count)
        return filesRoot.paths[selectedFileRoot];
    else
        return 0;
}

void Tree_Go_Next(void)
{
    Go_Offset_OrDieTrying(1);
}

void Tree_Go_Previous(void)
{
    Go_Offset_OrDieTrying(-1);
}


static void CleanUpPath(char* path)
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

static void Go_Offset_OrDieTrying(int offset)
{
    const int start = selectedFileRoot;
    int newPos = selectedFileRoot;
    newPos += offset;
    while(start != newPos)
    {
        if (SupportedFileFormat(filesRoot.paths[newPos]))
            goto Done;
        newPos += offset;
        if (newPos < 0)
            newPos = filesRoot.count - 1;
        else if (newPos >= (int)filesRoot.count)
            newPos = 0;
    }
Done:
    selectedFileRoot = newPos;
}

static bool SupportedFileFormat(const char* path)
{
    if (!path)
        return false;

    return
        IsFileExtension(path, ".png") ||
        IsFileExtension(path, ".jpeg") ||
        IsFileExtension(path, ".jpg") ||
        IsFileExtension(path, ".bmp") || 
        IsFileExtension(path, ".dds") || 
        IsFileExtension(path, ".gif"); 
}
