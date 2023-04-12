set(CURRENT_DIR "code")
set(CURRENT_FILES
    "raylib_wrapper.h"
    "main.c"
    "TextureToScreen.h"
    "TextureToScreen.c"
    "UserInterface.h"
    "UserInterface.c"
)
list(TRANSFORM CURRENT_FILES PREPEND "${CURRENT_DIR}/")
source_group("${CURRENT_DIR}" FILES "${CURRENT_FILES}")
list(APPEND SRC_FILES ${CURRENT_FILES})
#add_subdirectory(input)
#add_subdirectory(screens)
#add_subdirectory(utils)
set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
