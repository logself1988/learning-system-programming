set(TARGETS ex_copy1;
  ex_copy2;
  ex_move;
  ex_cons_des;
  ex_access_elem;
  ex_palindrome)

foreach(target ${TARGETS})
  MESSAGE(STATUS "TARGET: " ${target})
  add_executable(${target} ${target}.cc)
  target_link_libraries (${target} PUBLIC ${GRAPH_LIBS})
  target_include_directories(${target} ${FLTK_INCLUDE_DIRS})
endforeach()
