add_library (PathTracer.RayCast OBJECT
    ray.cpp
    camera.cpp
    hit.cpp
    )

target_include_directories (
    PathTracer.RayCast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )