cmake_minimum_required(VERSION 3.16)
project (sys_prop)

###############################################################################
# try_compile
try_compile(HAS_FOOBAR_CALL
    ${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/testNeedFoobar.c)

message (STATUS "HAS_FOOBAR_CALL=${HAS_FOOBAR_CALL}")

###############################################################################
# try_run
try_run (RUN_RESULT_VAR
    COMPILE_RESULT_VAR
    ${CMAKE_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/Modules/testByteOrder.c
    OUTPUT_VARIABLE OUTPUT)

message (STATUS "RUN_RESULT_VAR=${RUN_RESULT_VAR}")
message (STATUS "COMPILE_RESULT_VAR=${COMPILE_RESULT_VAR}")
message (STATUS "OUTPUT=${OUTPUT} .")

###############################################################################
# file WRITE
file (WRITE
    ${CMAKE_BINARY_DIR}/CMakeTemp/testCCompiler.c
    "int main() {return 0;}")

try_compile (CMAKE_C_COMPILER_WORKS
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/CMakeTemp/testCCompiler.c
    OUTPUT_VARIABLE OUTPUT)

message (STATUS "CMAKE_C_COMPILER_WORKS=${CMAKE_C_COMPILER_WORKS}")
