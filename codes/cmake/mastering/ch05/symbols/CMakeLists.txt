cmake_minimum_required(VERSION 3.16)
project (symbols C)

include (CheckIncludeFiles)
include (CheckLibraryExists)
include (CheckSymbolExists)
include (CheckTypeSize)

set (CMAKE_PROJECT_INCLUDE ${CMAKE_PROJECT_INCLUDE} /usr/include /usr/local/include)

#message (STATUS "CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}\n" 
#    "CMAKE_SYSTEM_INCLUDE_PATH=${CMAKE_SYSTEM_INCLUDE_PATH}\n"
#    "CMAKE_INCLUDE_PATH=${CMAKE_INCLUDE_PATH}\n"
#    "CMAKE_PROJECT_INCLUDE=${CMAKE_PROJECT_INCLUDE}" )

###############################################################################
# check for header files
set (INCLUDES "")

CHECK_INCLUDE_FILES (sys/socket.h HAVE_SOCKET_H)        # ???
if (HAVE_SOCKET_H)
    set (INCLUDES ${INCLUDES} sys/socket.h)
endif (HAVE_SOCKET_H)

CHECK_INCLUDE_FILES ("${INCLUDES};io.h" HAVE_IO_H)
if (HAVE_IO_H)
    set (INCLUDES ${INCLUDES} io.h)
endif (HAVE_IO_H)

message (STATUS "INCLUDES=${INCLUDES}")

###############################################################################
# check for libraries
set (LIBS "")

CHECK_LIBRARY_EXISTS ("dl;${LIBS}" dlopen "" HAVE_LIBDL)
if (HAVE_LIBDL)
    set (LIBS ${LIBS} dl)
endif (HAVE_LIBDL)

CHECK_LIBRARY_EXISTS ("ucb;${LIBS}" gethostname "" HAVE_LIBUCB)
if (HAVE_LIBUCB)
    set (LIBC ${LIBS} ucb)
endif (HAVE_LIBUCB)

message (STATUS "LIBS=${LIBS}")

set (CMAKE_REQUIRED_LIBRARIES ${LIBS})

###############################################################################
# check for function symbols
CHECK_SYMBOL_EXISTS (socket "${INCLUDES}" HAVE_SOCKET)
CHECK_SYMBOL_EXISTS (poll "${INCLUDES}" HAVE_POLL)

message (STATUS "HAVE_SOCKET=${HAVE_SOCKET}")
message (STATUS "HAVE_POLL=${HAVE_POLL}")

###############################################################################
# check type size
CHECK_TYPE_SIZE (int SIZEOF_INT)
CHECK_TYPE_SIZE (size_t SIZEOF_SIZE_T)

message (STATUS "SIZEOF_INT=${SIZEOF_INT}")
message (STATUS "SIZEOF_SIZE_T=${SIZEOF_SIZE_T}")
