add_library (PathTracer.SceneTest OBJECT
    triangleTest.cpp
    sceneTest.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src)

target_include_directories (
    PathTracer.SceneTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)