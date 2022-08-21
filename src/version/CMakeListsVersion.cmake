# this file is intended to be included by other project CMakeLists.txt files
# in order to make the following PathTracer version variables available
#   PATHTRACER_MAJOR : Integer major number (e.g. 0, 1, 2)
#   PATHTRACER_MINOR : Integer minor number (e.g. 0, 1, 2)
#   PATHTRACER_PATCH : Integer patch number (e.g. 0, 1, 2)
#   PATHTRACER_VERSION : Full PATHTRACER verion string as MAJOR.MINOR.PATCH+BUILD (e.g. 1.0.5+255)

file (READ ${CMAKE_CURRENT_LIST_DIR}/Version.txt VERSION NEWLINE_CONSUME)
string (REPLACE "." ";" VERSION "${VERSION}")
string (REPLACE "\n" ";" VERSION "${VERSION}")
string (REPLACE "\r" ";" VERSION "${VERSION}")
list (GET VERSION 0 PATHTRACER_MAJOR)
list (GET VERSION 1 PATHTRACER_MINOR)
list (GET VERSION 2 PATHTRACER_PATCH)

file (READ ${CMAKE_CURRENT_LIST_DIR}/AppName.txt PATHTRACER_NAME)


set (PATHTRACER_VERSION "${PATHTRACER_MAJOR}.${PATHTRACER_MINOR}.${PATHTRACER_PATCH}")