set(CURRENT_DIR "src_code")
set(CURRENT_FILES
    "ImageLoader.h"
	"ImageLoader.c"
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
	"Window.h"
	"Window.c"
)
list(TRANSFORM CURRENT_FILES PREPEND "${CURRENT_DIR}/")
source_group("${CURRENT_DIR}" FILES "${CURRENT_FILES}")
list(APPEND SRC_FILES ${CURRENT_FILES})
set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
