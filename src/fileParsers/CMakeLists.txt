set (SourceFiles
     model.cpp
)

set(HeaderFiles
    model.h
)

add_library (PathTracer.FileParsers OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.FileParsers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)