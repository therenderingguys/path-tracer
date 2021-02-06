add_library (PathTracer.RayCast OBJECT
    ray.cpp
    camera.cpp
    hit.cpp
    )

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.RayCast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )