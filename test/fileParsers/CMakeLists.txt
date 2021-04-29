add_library (PathTracer.FileParserTest OBJECT
    fileParserTest.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/objFiles
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sln
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)

target_include_directories (
    PathTracer.FileParserTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)