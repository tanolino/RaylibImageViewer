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

IF (MSVC)
	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
			 FILES ${CURRENT_FILES})
ELSE()
    add_compile_options(-Wall -Wextra -Wpedantic)
ENDIF ()

include_directories(${raylib_public_headers})
add_executable(${PROJECT_NAME} ${CURRENT_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
