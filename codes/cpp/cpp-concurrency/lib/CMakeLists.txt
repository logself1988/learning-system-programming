add_library(cppcon log.h)
target_link_libraries(cppcon ${LOG_LIBS})
set_target_properties(cppcon PROPERTIES LINKER_LANGUAGE CXX)
