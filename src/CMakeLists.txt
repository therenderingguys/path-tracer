project(PathTracer)

#Look up OpenGL
find_package(OpenGL REQUIRED)

#Link GLAD
add_subdirectory(${CMAKE_SOURCE_DIR}/packages/glad/ ${CMAKE_CURRENT_BINARY_DIR}/glad)
include_directories(${CMAKE_SOURCE_DIR}/packages/glad/include)

# PathTracer Src dir
set(PATH_TRACER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(${glfw3_FOUND})
   MESSAGE(STATUS "Found GLFW3.")
else()
    MESSAGE(STATUS "Could not locate GLFW3, downloading.")
    download_file(https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip
                 ${CMAKE_SOURCE_DIR}/packages/glfw-3.3.2.zip
                 MD5
                 f794d9ad899a64894782884be79d644b)
    decompress(${CMAKE_SOURCE_DIR}/packages/glfw-3.3.2.zip ${CMAKE_SOURCE_DIR}/packages/glfw)
    add_subdirectory(${CMAKE_SOURCE_DIR}/packages/glfw/ ${CMAKE_CURRENT_BINARY_DIR}/glfw)
    include_directories(${CMAKE_SOURCE_DIR}/packages/glfw/include)
endif()

if(${GLM_FOUND})
    MESSAGE(STATUS "Found GLM.")
else()
    MESSAGE(STATUS "Could not locate GLM, downloading.")
    download_file(https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
              ${CMAKE_SOURCE_DIR}/packages/glm-0.9.9.8.zip
              MD5
              69895110052f0d711c9c54fbf385f6f5)
    decompress(${CMAKE_SOURCE_DIR}/packages/glm-0.9.9.8.zip ${CMAKE_SOURCE_DIR}/packages/glm)
    include_directories(${CMAKE_SOURCE_DIR}/packages/glm)
endif()

if(APPLE)
  message(STATUS "APPLE Platform detected")
  include_directories(/System/Library/Frameworks)
  include_directories(/usr/local/include)
  find_library(COCOA_LIBRARY Cocoa REQUIRED)
  find_library(OpenGL_LIBRARY OpenGL)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
  set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

if(LINUX)
  set(EXTRA_LIBS ${CMAKE_DL_LIBS})
endif()

add_library (${PROJECT_NAME} STATIC
  PathTracerStatic.cpp
  $<TARGET_OBJECTS:PathTracer.FileParsers>
  $<TARGET_OBJECTS:PathTracer.RayCast>
  $<TARGET_OBJECTS:PathTracer.Renderer>
  $<TARGET_OBJECTS:PathTracer.Scene>
  $<TARGET_OBJECTS:PathTracer.Window>
  $<TARGET_OBJECTS:PathTracer.Version>
)

set(GL_LIBS OpenGL::GL glfw glad ${EXTRA_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GL_LIBS})

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  # Add include_directories here
  fileParsers
  raycast
  renderer
  scene
  window
)

add_subdirectory(main)
add_subdirectory(fileParsers)
add_subdirectory(raycast)
add_subdirectory (renderer)
add_subdirectory(scene)
add_subdirectory(window)
add_subdirectory (version)