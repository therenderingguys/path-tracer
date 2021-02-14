set (SourceFiles
     camera.cpp
     hit.cpp
     ray.cpp
)

set(HeaderFiles
    camera.h
    hit.h
    ray.h 
)

add_library (PathTracer.RayCast OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.RayCast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)