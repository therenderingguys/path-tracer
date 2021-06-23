set (SourceFiles
     scene.cpp
     triangle.cpp
     light.cpp
)

set(HeaderFiles
    scene.h
    triangle.h
    light.h
)

add_library (PathTracer.Scene OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${PATH_TRACER_SOURCE_DIR}
)