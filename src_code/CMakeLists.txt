set(CURRENT_DIR "src_code")
set(CURRENT_FILES
    "main.c"
    "raylib_wrapper.h"
	"StringUtils.h"
	"StringUtils.c"
    "TextureToScreen.h"
    "TextureToScreen.c"
	"Tree.h"
	"Tree.c"
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
