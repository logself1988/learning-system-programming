add_executable(ex_fltk ex_fltk.cc)
target_link_libraries (ex_fltk ${FLTK_LIBS})
target_include_directories(ex_fltk ${FLTK_INCLUDE_DIRS})
