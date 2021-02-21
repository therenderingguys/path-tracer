add_library (PathTracer.RendererTest OBJECT
    rendererTest.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src)

target_include_directories (
    PathTracer.RendererTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)