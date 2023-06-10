#ifndef TREE_HEADER
#define TREE_HEADER

void        Tree_RegisterStart(const char* start);
void        Tree_CleanUp(void);
const char* Tree_GetCurrent(void); // Might return 0 on error state
void        Tree_Go_Next(void);
void        Tree_Go_Previous(void);

#endif // TREE_HEADER
