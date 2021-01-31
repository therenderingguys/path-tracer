project(PathTracer)
cmake_minimum_required(VERSION 3.10)
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
    if(WIN32)
        execute_process (
            COMMAND cmd.exe /c mkdir ${path}
            COMMAND powershell.exe -ExecutionPolicy Bypass Expand-Archive -LiteralPath ${tarfile} -DestinationPath ${path}
        )
        execute_process (
            COMMAND powershell.exe -ExecutionPolicy Bypass -Command "${CMAKE_SOURCE_DIR}/scripts/moveFiles.ps1 ${path} ${tarfile}"
        )
    elseif(LINUX AND ${FILE_EXT} STREQUAL ".zip")
        get_filename_component(PATH_PARENT ${path} DIRECTORY)
        execute_process (
            COMMAND unzip -qq ${tarfile} -d ${PATH_PARENT}
        )
        execute_process (
            COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/renameDir.sh ${path} ${tarfile}"
        )
    else()
        execute_process (
            COMMAND mkdir ${path}
            COMMAND tar -xzvf ${tarfile} -C ${path} --strip-components 1
        )
    endif()
endif()

endfunction(decompress)
download_file(https://gist.github.com/farzonl/f724000a4fd841c792c82a36c0da8cba/raw/b6125287d4364e0982c970045691bf6d319c9868/glad.zip
              ${CMAKE_SOURCE_DIR}/packages/glad.zip 
              MD5
              262e8984dbde2f359207ffa8e609aa50)

decompress(${CMAKE_SOURCE_DIR}/packages/glad.zip ${CMAKE_SOURCE_DIR}/packages/glad)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11" )

add_subdirectory(src)
add_subdirectory (test)