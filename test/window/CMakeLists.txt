add_library (PathTracer.WindowTest OBJECT
    windowTest.cpp
    pixelBufferTest.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/packages/glad/include)

target_include_directories (
    PathTracer.SceneTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)