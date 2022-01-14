set(antlr_lib_url
    "https://www.antlr.org/download/antlr4-cpp-runtime-4.9.3-macos.zip")
set(antlr_lib_archive "antlr4-cpp-runtime-4.9.3-macos.zip")
set(antlr_lib_dir "antlr")

if (EXISTS "${CMAKE_BINARY_DIR}/${antlr_lib_archive}")
  message("Found ${antlr_lib_archive}")
else()
  file(DOWNLOAD
    "${antlr_lib_url}"
    "${CMAKE_BINARY_DIR}/${antlr_lib_archive}"
    SHOW_PROGRESS)

    message("Extracting ${CMAKE_BINARY_DIR}/${antlr_lib_archive}")
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/${antlr_lib_dir}/"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${antlr_lib_archive}" "${CMAKE_BINARY_DIR}/${antlr_lib_dir}/"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/${antlr_lib_dir}/${antlr_lib_archive}"
    COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_BINARY_DIR}/${antlr_lib_dir}" tar xvzf "${CMAKE_BINARY_DIR}/${antlr_lib_archive}")
endif()

# header files
include_directories("${CMAKE_BINARY_DIR}/${antlr_lib_dir}/antlr4-runtime")

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorBaseVisitor.cpp ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorLexer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorParser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorVisitor.cpp
  COMMAND java -jar /usr/local/lib/antlr-4.9.2-complete.jar -Dlanguage=Cpp ${CMAKE_CURRENT_SOURCE_DIR}/Calculator.g4 -visitor -no-listener
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Calculator.g4
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)
add_executable(test_Calculator test_Calculator.cc
  CalculatorBaseVisitor.cpp
  CalculatorLexer.cpp
  CalculatorParser.cpp
  CalculatorVisitor.cpp)

# # lib files
target_link_libraries(test_Calculator "${CMAKE_BINARY_DIR}/${antlr_lib_dir}/lib/libantlr4-runtime.a")