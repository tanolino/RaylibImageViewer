#ifndef TREE_HEADER
#define TREE_HEADER

void        Tree_RegisterStart(const char* start);
void        Tree_CleanUp();
const char* Tree_GetCurrent();
void        Tree_Go_Next();
void        Tree_Go_Previous();

#endif // TREE_HEADER
