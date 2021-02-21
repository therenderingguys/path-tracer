project(PathTracer_exe)

set(SOURCE_FILES
                 # add files here
                 main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries (${PROJECT_NAME}
  PathTracer
  ${GL_LIBS}
  glad
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  # Add include_directories here
)