cmake_minimum_required (VERSION 3.16)

project (cp5 CXX)

# C99, C++11
set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 11)

# 库
## spdlog
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

# 子目录
add_subdirectory (ch01)
add_subdirectory (ch02)
