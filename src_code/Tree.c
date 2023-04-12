#include "Tree.h"

#include <stdlib.h>
#include <raylib.h>
#include <stdbool.h>

#include "StringUtils.h"

// Helpful functions for creating structures //

struct Node {
    char* folder_name;
    struct Leaf* sub_leafs;
    int sub_leaf_count;
    struct Node* sub_nodes;
    int sub_node_count;
    int selected_element;
};

bool InitLeaf(struct Leaf* leaf, const char* path);
bool InitNode(struct Node* node, const char* path);
void ClearLeaf(struct Leaf* leaf);
void ClearNode(struct Node* node);

// Helpful functions //
struct Leaf* WalkDownTree(struct Node* node);

// State //
static const char* treeStartsHere = 0;
static struct Node* treeRoot = 0;

// Externally used Functions //
void Tree_RegisterStart(const char* start)
{
    treeStartsHere = start;
}

void Tree_CleanUp()
{
    ClearNode(treeRoot);
    free(treeRoot);
    treeRoot = 0;
}


const struct Leaf* Tree_GetCurrent()
{
    // TODO Fix the init
    if (treeRoot == 0)
    {
        // Fill the tree root
        const bool file_exists      = FileExists(treeStartsHere);
        const bool directory_exists = DirectoryExists(treeStartsHere);
        if (!file_exists && !directory_exists)
        {
            return 0;
        }

        treeRoot = malloc(sizeof(struct Node));
        if (file_exists)
        {
            char* tmp;
            const char* volatileStr = GetDirectoryPath(treeStartsHere);
            if (!StringDuplicate(&tmp, volatileStr, 4096))
            {
                perror("Failed to duplicate string :\n%s", volatileStr);
                return 0;
                
            }

            bool initNodeSuccess = InitNode(treeRoot, tmp);
            free(tmp);

            if (!initNodeSuccess)
            {
                ClearNode(treeRoot);
                free(treeRoot);
                treeRoot = 0;
                return 0;
            }
        }
        else // if (directory_exists)
        {
            treeRoot = malloc(sizeof(struct Node));
            if (!InitNode(treeRoot, treeStartsHere))
            {
                ClearNode(treeRoot);
                free(treeRoot);
                treeRoot = 0;
                return 0;
            }
        }
    }

    return WalkDownTree(treeRoot);
}

// Helpful functions //
struct Leaf* WalkDownTree(struct Node* node)
{
    struct Node* tmp = node;
    while (tmp != 0)
    {
        if (tmp->selected_element >= tmp->sub_leaf_count)
        {
            int sel = tmp->selected_element - tmp->sub_leaf_count;
            if (sel >= tmp->sub_node_count)
                tmp = 0;
            else
                tmp = tmp->sub_nodes + sel;
        }
        else
        {
            return tmp->sub_leafs + tmp->selected_element;
        }
    }
    return 0; // We should never end up here
}

// Helpful functions for creating structures //
bool InitLeaf(struct Leaf* leaf, const char* path)
{
    leaf->file_name = 0;
    return StringDuplicate(&leaf->file_name, GetFileName(path), 4096);
}

bool InitNode(struct Node* node, const char* path)
{
    node->folder_name = 0;
    node->sub_leafs = 0;
    node->sub_leaf_count = 0;
    node->sub_nodes = 0;
    node->sub_node_count = 0;
    node->selected_element = 0;

    if (!StringDuplicate(&node->folder_name, GetFileName(path), 4096))
        return false;
    return true;
}

void ClearLeaf(struct Leaf* leaf)
{
    if (leaf == 0)
        return;
    free(leaf->file_name);
    leaf->file_name = 0;
}

void ClearNode(struct Node* node)
{
    if (node == 0)
        return;

    free(node->folder_name);
    node->folder_name = 0;

    if (node->sub_leafs != 0)
    {
        for (int i = 0; i < node->sub_leaf_count; ++i)
        {
            ClearLeaf(node->sub_leafs + i);
        }
        free(node->sub_leafs);
        node->sub_leafs = 0;
        node->sub_leaf_count = 0;
    }

    if (node->sub_nodes != 0)
    {
        for (int i = 0; i < node->sub_node_count; ++i)
        {
            ClearNode(node->sub_nodes + i);
        }
        free(node->sub_nodes);
        node->sub_nodes = 0;
        node->sub_node_count = 0;
    }
}
