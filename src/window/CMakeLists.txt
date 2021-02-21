set (SourceFiles
     glfwWindow.cpp
     window.cpp
)

set(HeaderFiles
    glfwWindow.h
    window.h
    singleton.h
)

add_library (PathTracer.Window OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${PATH_TRACER_SOURCE_DIR})

target_include_directories (
    PathTracer.Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )