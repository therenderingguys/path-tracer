add_library (PathTracer.RayCastTest OBJECT
    rayTest.cpp
    cameraTest.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src/raycast)

target_include_directories (
    PathTracer.RayCastTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)