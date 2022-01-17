add_executable(ex_shape ex_shape.cc)
target_link_libraries (ex_shape PUBLIC ${GRAPH_LIBS})
target_include_directories(ex_shape ${FLTK_INCLUDE_DIRS})
