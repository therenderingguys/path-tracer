add_library (PathTracer.Scene OBJECT
    triangle.cpp
    )

target_include_directories (
    PathTracer.Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )