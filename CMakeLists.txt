project(path_tracer)
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
    if(WIN32)
        execute_process (
            COMMAND cmd.exe /c mkdir ${path}
            #COMMAND 7z x ${tarfile}  -o${path} #Note Expand-Archive can be slow can replace with 7z
            COMMAND powershell.exe -ExecutionPolicy Bypass Expand-Archive -LiteralPath ${tarfile} -DestinationPath ${path}
        )
        execute_process (
            COMMAND powershell.exe -ExecutionPolicy Bypass -Command "${CMAKE_SOURCE_DIR}/scripts/moveFiles.ps1 ${path} ${tarfile}"
        )
    else()
        execute_process (
            COMMAND mkdir ${path}
            COMMAND tar -xzvf ${tarfile} -C ${path} --strip-components 1
        )
    endif()
endif()

endfunction(decompress)

download_file(https://gist.github.com/farzonl/f724000a4fd841c792c82a36c0da8cba/raw/8d40f11699eb0a5b428e71632735aca0a192375f/glad.zip
             ${CMAKE_SOURCE_DIR}/packages/glad.zip 
             MD5
             7fa678ef655083fa173a5c677a199ba3)

decompress(${CMAKE_SOURCE_DIR}/packages/glad.zip ${CMAKE_SOURCE_DIR}/packages/glad)

#add_subdirectory(packages/glad/)
add_subdirectory(src)