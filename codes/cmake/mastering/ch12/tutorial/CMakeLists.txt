cmake_minimum_required(VERSION 3.16)
project (Tutorial)

###############################################################################
# Version
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

###############################################################################
# system introspection
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

message (STATUS "HAVE_LOG=${HAVE_LOG}, HAVE_EXP=${HAVE_EXP}")

###############################################################################
# confgiure header files
configure_file (
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_BINARY_DIR}/TutorialConfig.h")

include_directories ("${PROJECT_BINARY_DIR}")

###############################################################################
# add MathFunctions?
option (USE_MYMATH "Use tutorial provided math implenmentation" ON)
if (USE_MYMATH)
    include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
    add_subdirectory (MathFunctions)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

###############################################################################
# add executable
add_executable(Tutorial tutorial.cxx)
target_link_libraries (Tutorial ${EXTRA_LIBS})

###############################################################################
# install
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

###############################################################################
# test ???
macro (do_test arg result)
    add_test (TutorialComp${arg} Tutorial ${arg})
    set_tests_properties (TutorialComp${arg}
        PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

do_test (25 "25 is 5")
do_test (-25 "-25 is -nan")

include (CTest)
