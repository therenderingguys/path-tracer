add_library (PathTracer.Renderer OBJECT
    renderer.cpp
    )

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${PATH_TRACER_SOURCE_DIR}
    )