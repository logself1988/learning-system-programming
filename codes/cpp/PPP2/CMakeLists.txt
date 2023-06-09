cmake_minimum_required (VERSION 3.16)

project (ppp2 CXX)

# C99, C++14
set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 14)

# Options
option (PPP2_DEBUG "Build with extra debug pring message" ON)
if (PPP2_DEBUG)
  add_definitions (-DPPP2_DEBUG)
endif (PPP2_DEBUG)
MESSAGE("PPP2_DEBUG: " ${PPP2_DEBUG})

# 库
## 1 FLTK
## https://cmake.org/cmake/help/latest/module/FindFLTK.html
if(NOT TARGET fltk)
    find_package(fltk REQUIRED)
    if(FLTK_FOUND)
        MESSAGE("Found fltk") # no version
    endif(FLTK_FOUND)
endif()
set (FLTK_LIBS PRIVATE ${FLTK_LIBRARIES})
MESSAGE("FLTK_LIBS:" ${FLTK_LIBS})
set (FLTK_INCLUDE_DIRS PRIVATE ${FLTK_INCLUDE_DIR})
MESSAGE("FLTK_INCLUDE_DIRS:" ${FLTK_INCLUDE_DIRS})

## 2 spdlog
## 日志库: https://github.com/gabime/spdlog
if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
    if(spdlog_FOUND)
        MESSAGE("Found spdlog: " ${spdlog_VERSION})
    endif(spdlog_FOUND)
endif()
set(LOG_LIBS PRIVATE spdlog::spdlog)
MESSAGE("LOG_LIBS:" ${LOG_LIBS})

## 本地库
include_directories("${PROJECT_SOURCE_DIR}/lib")
SET(GRAPH_LIBS graph)
include_directories("${PROJECT_SOURCE_DIR}/lib/graph")
add_subdirectory(lib/graph)

# 子目录
# add_subdirectory (ch02)
# add_subdirectory (ch06)
# add_subdirectory (ch07)
# add_subdirectory (ch09)
# add_subdirectory (ch10)

# add_subdirectory(ch12)
# add_subdirectory(ch13)
# add_subdirectory(ch14)
# add_subdirectory(ch15)

# add_subdirectory(ch17)
# add_subdirectory(ch18)
add_subdirectory(ch19)

# add_subdirectory (appendix_d)
# add_subdirectory (ex_antlr)