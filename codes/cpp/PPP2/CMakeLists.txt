cmake_minimum_required (VERSION 3.16)

project (ppp2 CXX)

# C99, C++14
set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 14)

# Cmake: Configure Arguments
# -DPPP2_DEBUG=ON
option (PPP2_DEBUG "Build with extra debug pring message" ON)
if (PPP2_DEBUG)
  add_definitions (-DPPP2_DEBUG)
endif (PPP2_DEBUG)
MESSAGE("PPP2_DEBUG: " ${PPP2_DEBUG})

# 库

## https://cmake.org/cmake/help/latest/module/FindFLTK.html
if(NOT TARGET fltk)
    find_package(fltk REQUIRED)
    if(FLTK_FOUND)
        MESSAGE("Found fltk")
    endif(FLTK_FOUND)
endif()
set (EXTRA_LIBS
  PRIVATE ${FLTK_LIBRARIES})
MESSAGE("EXTRA_LIBS:" ${EXTRA_LIBS})
set (EXTRA_INCLUDE_DIRS
  PRIVATE ${FLTK_INCLUDE_DIR})
MESSAGE("EXTRA_INCLUDE_DIRS:" ${EXTRA_INCLUDE_DIRS})

## 本地库
include_directories("${PROJECT_SOURCE_DIR}/lib")

# 子目录
add_subdirectory (ch02)
add_subdirectory (ch06)
add_subdirectory (ch07)
add_subdirectory (ch09)
add_subdirectory (appendix_d)
# add_subdirectory (ex_antlr)