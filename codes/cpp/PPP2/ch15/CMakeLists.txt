set(TARGETS ex01_simple_function;
  ex02_function;
  ex03_approximation;
  ex04_graphing_data)

foreach(target ${TARGETS})
  MESSAGE(STATUS "TARGET: " ${target})
  add_executable(${target} ${target}.cc)
  target_link_libraries (${target} PUBLIC ${GRAPH_LIBS})
  target_include_directories(${target} ${FLTK_INCLUDE_DIRS})
endforeach()
