cmake_minimum_required(VERSION 3.16)
project (modules)

#set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/cmake-3.16/Modules/")
message (STATUS "CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")
include (FindZLIB)

if (ZLIB_FOUND)
    message (STATUS "Found ZLIB!!!")
endif (ZLIB_FOUND)