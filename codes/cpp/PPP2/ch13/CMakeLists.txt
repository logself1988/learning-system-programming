set(TARGETS ex01_line; 
  ex02_lines;
  ex03_color;
  ex04_line_style;
  ex05_open_polyline;
  ex06_closed_polyline;
  ex07_polygon;
  ex08_rectangle;
  ex09_unnamed_objects;
  ex10_text;
  ex11_circle;
  ex12_ellipse;
  ex13_marked_polyline;
  ex14_marks;
  ex15_mark;
  ex16_image)

foreach(target ${TARGETS})
  MESSAGE(STATUS "TARGET: " ${target})
  add_executable(${target} ${target}.cc)
  target_link_libraries (${target} PUBLIC ${GRAPH_LIBS})
  target_include_directories(${target} ${FLTK_INCLUDE_DIRS})
endforeach()
