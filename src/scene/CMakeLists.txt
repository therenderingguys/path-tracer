add_library (PathTracer.Scene OBJECT
    triangle.cpp
    scene.cpp
    )

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${PATH_TRACER_SOURCE_DIR}
    )