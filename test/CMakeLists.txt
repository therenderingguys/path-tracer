project(${CMAKE_PROJECT_NAME}_TEST)

download_file(https://github.com/catchorg/Catch2/releases/download/v2.13.0/catch.hpp 
              ${CMAKE_SOURCE_DIR}/packages/catch2/catch.hpp
              MD5
              209cbb2f8f37224cc5f7261cf9388bc2)

include_directories(${CMAKE_SOURCE_DIR}/packages/)

if (APPLE)
  include_directories(/usr/local/include)
endif()

if(NOT ${GLM_FOUND})
  include_directories(${CMAKE_SOURCE_DIR}/packages/glm)
endif()

add_executable(${PROJECT_NAME}
               $<TARGET_OBJECTS:PathTracer.FileParserTest>
               $<TARGET_OBJECTS:PathTracer.RayCastTest>
               $<TARGET_OBJECTS:PathTracer.SceneTest>
               $<TARGET_OBJECTS:PathTracer.RendererTest>
               $<TARGET_OBJECTS:PathTracer.WindowTest>
               test.cpp
)

target_link_libraries (${PROJECT_NAME}
  PathTracer
)

add_subdirectory(fileParsers)
add_subdirectory (raycast)
add_subdirectory (renderer)
add_subdirectory (scene)
add_subdirectory (window)