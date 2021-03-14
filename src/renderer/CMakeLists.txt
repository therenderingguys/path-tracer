set (SourceFiles
     shader.cpp
     renderer.cpp
)

set(HeaderFiles
    shader.h
    renderer.h
)

add_library (PathTracer.Renderer OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${PATH_TRACER_SOURCE_DIR}
    )