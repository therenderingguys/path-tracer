project(PathTracer)
cmake_minimum_required(VERSION 3.23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

function(download_file url filename hash_type hash)

if(NOT EXISTS ${filename})
  file(DOWNLOAD ${url} ${filename}
       TIMEOUT 60  # seconds
       EXPECTED_HASH ${hash_type}=${hash}
       TLS_VERIFY ON
      )
endif()

endfunction(download_file)

function(decompress tarfile path)
if(NOT EXISTS ${path})
    get_filename_component(FILE_EXT ${tarfile} LAST_EXT)
    get_filename_component(PATH_PARENT ${path} DIRECTORY)
    if(WIN32)
        execute_process (
            COMMAND powershell.exe -ExecutionPolicy Bypass Expand-Archive -LiteralPath ${tarfile} -DestinationPath ${PATH_PARENT}
        )
        execute_process (
            COMMAND powershell.exe -ExecutionPolicy Bypass -Command "${CMAKE_SOURCE_DIR}/scripts/renameDir.ps1 ${path} ${tarfile}"
        )
    elseif(LINUX AND ${FILE_EXT} STREQUAL ".zip")
        execute_process (
            COMMAND unzip -qq ${tarfile} -d ${PATH_PARENT}
        )
        execute_process (
            COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/renameDir.sh ${path} ${tarfile}"
        )
    else()
        execute_process ( COMMAND mkdir -p ${path})
        execute_process (COMMAND tar -xzvf ${tarfile} -C ${path} --strip-components 1)
    endif()
endif()

endfunction(decompress)

download_file(https://gist.github.com/farzonl/f724000a4fd841c792c82a36c0da8cba/raw/b6125287d4364e0982c970045691bf6d319c9868/glad.zip
              ${CMAKE_SOURCE_DIR}/packages/glad.zip 
              MD5
              262e8984dbde2f359207ffa8e609aa50)

decompress(${CMAKE_SOURCE_DIR}/packages/glad.zip ${CMAKE_SOURCE_DIR}/packages/glad)



if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

 # Note this is primarily done for MSVC which 
 # doesn't run from path-tracer dir. However its
 # good practice to package the shaders with the binary.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/main)
 
find_package(GLM) # Look up GLM
find_package(glfw3 3.3) # Look up glfw

add_subdirectory (src)
add_subdirectory (test)