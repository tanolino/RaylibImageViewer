cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "RaylibImageViewer")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
# set(LLVM_CXX_STD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
	${PROJECT_NAME}
	VERSION 0.1
	DESCRIPTION "A sample project using raylib."
	)

set(SRC_FILES "") # Filled by add_subdirectory
add_subdirectory("src_code")
IF (MSVC)
	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
			 FILES ${SRC_FILES})
ELSE()
    add_compile_options(-Wall -Wextra -Wpedantic -march=x86-64)
ENDIF ()


#---------------- Configure Compiler Flags ---------------------
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
	# We compile with Emscripten
	message(STATUS " * C++ compiler: Emscripten")
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
	set(PLATFORM Web)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH -s INITIAL_MEMORY=33554432")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
else()
	# We compile for a normal pc
	message(STATUS " * C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
	# set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    # set(CMAKE_BUILD_TYPE "Release")
	set(BUILD_SHARED_LIBS OFF)
	set(OpenGL_GL_PREFERENCE "GLVND")

	set(ADDITIONAL_LINK_LIBRARIES_STATIC "-static-libgcc -static-libstdc++")
		
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		# using Clang
		set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${ADDITIONAL_LINK_LIBRARIES_STATIC})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		# using GCC
		set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${ADDITIONAL_LINK_LIBRARIES_STATIC})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
		# using Intel C++
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		# using Visual Studio C++)
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
		set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
	endif()
endif()
#----------------------------------------------------------------


#------------- Configure Raylib -------------
set(CUSTOMIZE_BUILD ON)
set(SUPPORT_QUADS_DRAW_MODE ON)
set(SUPPORT_DEFAULT_FONT ON)
set(SUPPORT_MODULE_RMODELS OFF)
set(SUPPORT_FILEFORMAT_ASTC OFF)
set(SUPPORT_FILEFORMAT_BMP ON)
set(SUPPORT_FILEFORMAT_DDS ON)
set(SUPPORT_FILEFORMAT_FLAC OFF)
set(SUPPORT_FILEFORMAT_FNT OFF)
set(SUPPORT_FILEFORMAT_GIF ON)
set(SUPPORT_FILEFORMAT_GLTF OFF)
set(SUPPORT_FILEFORMAT_HDR OFF)
set(SUPPORT_FILEFORMAT_IQM OFF)
set(SUPPORT_FILEFORMAT_JPG ON)
set(SUPPORT_FILEFORMAT_KTX OFF)
set(SUPPORT_FILEFORMAT_MOD OFF)
set(SUPPORT_FILEFORMAT_MP3 OFF)
set(SUPPORT_FILEFORMAT_MTL OFF)
set(SUPPORT_FILEFORMAT_OBJ OFF)
set(SUPPORT_FILEFORMAT_OGG OFF)
set(SUPPORT_FILEFORMAT_PKM OFF)
set(SUPPORT_FILEFORMAT_PNG ON)
set(SUPPORT_FILEFORMAT_PNM OFF)
set(SUPPORT_FILEFORMAT_PSD OFF)
set(SUPPORT_FILEFORMAT_TTF OFF)
set(SUPPORT_FILEFORMAT_VOX OFF)
set(SUPPORT_FILEFORMAT_WAV OFF)
set(SUPPORT_FILEFORMAT_XM OFF)
set(SUPPORT_GESTURES_SYSTEM OFF)
set(SUPPORT_GIF_RECORDING OFF)
set(SUPPORT_IMAGE_EXPORT OFF)
set(SUPPORT_IMAGE_GENERATION OFF)
set(SUPPORT_IMAGE_MANIPULATION OFF)
set(SUPPORT_MESH_GENERATION OFF)
set(SUPPORT_MODULE_RAUDIO OFF)
set(SUPPORT_MODULE_RSHAPES ON)
set(SUPPORT_MOUSE_GESTURES OFF)
set(SUPPORT_SCREEN_CAPTURE OFF)
set(USE_AUDIO ON)

add_subdirectory("raylib")
#---------------------------------------------


include_directories("${CMAKE_SOURCE_DIR}/code" ${raylib_public_headers})
message(DEBUG "Source Files: " ${SRC_FILES})
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
