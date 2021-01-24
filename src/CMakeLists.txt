project(path_tracer)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11  " )

set(SOURCE_FILES
                 # add files here
                 main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#Look up OpenGL
find_package(OpenGL REQUIRED)

# Look up glfw
find_package(glfw3 3.3 REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/packages/glad/ ${CMAKE_CURRENT_BINARY_DIR}/glad)

# Look up GLM
find_package(GLM REQUIRED)

if (APPLE)
    message(STATUS "APPLE Platform detected")
    include_directories(/System/Library/Frameworks)
    include_directories(/usr/local/include)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)

set(GL_LIBS OpenGL::GL glm glfw ${EXTRA_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GL_LIBS} glad)

add_subdirectory (test)
