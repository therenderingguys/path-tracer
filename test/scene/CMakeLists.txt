add_library (PathTracer.SceneTest OBJECT
    triangle.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src/scene)

target_include_directories (
    PathTracer.SceneTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)