MESSAGE("building ${GRAPH_LIBS} lib")
add_library(${GRAPH_LIBS} 
  Simple_window.h
  Window.cc window.h
  Graph.cc Graph.h
  GUI.cc GUI.h)
target_link_libraries(${GRAPH_LIBS} ${FLTK_LIBS} ${LOG_LIBS})
target_include_directories(${GRAPH_LIBS} ${FLTK_INCLUDE_DIRS})
