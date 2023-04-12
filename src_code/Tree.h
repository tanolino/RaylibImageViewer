#ifndef TREE_HEADER
#define TREE_HEADER

struct Leaf {
    char* file_name;
};

void               Tree_RegisterStart(const char* start);
void               Tree_CleanUp();
const struct Leaf* Tree_GetCurrent();

#endif // TREE_HEADER
