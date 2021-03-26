set (SourceFiles
     rectangle.cpp
     renderer.cpp
     shader.cpp
     shape.cpp
     texture.cpp
     pixelBuffer.cpp
)

set(HeaderFiles
    rectangle.h
    renderer.h
    shader.h
    shape.h
    texture.h
    pixelBuffer.h
)

add_library (PathTracer.Renderer OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${PATH_TRACER_SOURCE_DIR}
    )