cmake_minimum_required (VERSION 3.16)

project (cpp-concurrency CXX)

# C99, C++17
set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 17)

# 库
## 日志库: https://github.com/gabime/spdlog
if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
    if(spdlog_FOUND)
        MESSAGE(STATUS "Found spdlog: " ${spdlog_VERSION})
    endif(spdlog_FOUND)
endif()
set(LOG_LIBS PRIVATE spdlog::spdlog)
MESSAGE(STATUS ${LOG_LIBS})
## 本地库
include_directories("${PROJECT_SOURCE_DIR}/lib")
set (EXTRA_LIBS 
  PUBLIC cppcon 
  PUBLIC pthread
  PRIVATE spdlog::spdlog)
MESSAGE(STATUS ${EXTRA_LIBS})
add_subdirectory (lib)

# 子目录
add_subdirectory (ch01)
