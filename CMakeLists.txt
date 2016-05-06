cmake_minimum_required (VERSION 2.8.9)

project(Engine)

# Place binary in main directory
SET(EXECUTABLE_OUTPUT_PATH ../)
SET(CMAKE_CXX_FLAGS "-std=c++11")

# OSX only flags
IF(APPLE)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
   FIND_LIBRARY(GLEW_LIBRARY GLEW )
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
   MARK_AS_ADVANCED (COCOA_LIBRARY
                     OpenGL_LIBRARY
                     IOKIT_LIBRARY
                     COREVIDEO_LIBRARY)
   SET(MAC_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
ENDIF (APPLE)

# All systems include these files
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Find glfw header
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h ${HEADER_SEARCH_PATH})
# Find glfw library
find_library(GLFW_LIBRARIES glfw3 ${LIBRARY_SEARCH_PATH})
link_libraries(${GLFW_LIBRARY_DIRS})
# Find assimp
find_package(assimp REQUIRED)

# Add the sources to the executable for linking
add_executable(Engine main.cpp Camera.cpp Mesh.cpp Model.cpp Shader.cpp Texture.cpp Transform.cpp Window.cpp)
# Link the libraries
target_link_libraries(Engine ${MAC_LIBS} ${GLFW_LIBRARY_DIRS} ${GLM_LIBRARY_DIRS} assimp glfw3)
