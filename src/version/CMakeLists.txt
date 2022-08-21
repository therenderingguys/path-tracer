

include ("CMakeListsVersion.cmake")

set(GIT_EXECUTABLE git)
set(PATHTRACER_DESCRIPTION "Path Tracer, A Custom Path Tracer Implementation.")

# the commit's SHA1, and whether the building workspace was dirty or not
execute_process(COMMAND
  "${GIT_EXECUTABLE}" rev-parse --short HEAD
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_SHA1
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# the date of the commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 --format=%ad --date=local
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_DATE
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# the subject of the commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 --format=%s
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_COMMIT_SUBJECT
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# the branch of the commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" branch --show-current
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_COMMIT_BRANCH
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)


# generate version.cpp
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/version.cpp" @ONLY)

set (SourceFiles
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
)

if(WIN32)
  include(generate_product_version.cmake)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  generate_product_version(
   VersionFilesOutputVariable
   NAME "${PATHTRACER_NAME}"
   ICON ${CMAKE_CURRENT_BINARY_DIR}/icon.ico
   VERSION_MAJOR ${PATHTRACER_MAJOR}
   VERSION_MINOR ${PATHTRACER_MINOR}
   VERSION_PATCH ${PATHTRACER_PATCH}
   #VERSION_REVISION 0 #could hook this up with the cli
   COMPANY_NAME ${PATHTRACER_NAME}
   FILE_DESCRIPTION ${PATHTRACER_DESCRIPTION}
   )
endif()


set(HeaderFiles
    version.h
)

add_library (PathTracer.Version OBJECT
            ${SourceFiles} ${HeaderFiles}
)
set_target_properties(PathTracer.Version PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories (
    PathTracer.Version PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
