LLVM_CONFIG?=llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

CLANGLIBS= \
  -Wl,--start-group\
  -lclang\
  -lclangFrontend\
  -lclangDriver\
  -lclangSerialization\
  -lclangParse\
  -lclangSema\
  -lclangAnalysis\
  -lclangEdit\
  -lclangAST\
  -lclangLex\
  -lclangBasic\
  -Wl,--end-group

LLVMLIBS=$(shell $(LLVM_CONFIG) --libs)

PROJECT=project
PROJECT_OBJECTS=project.o

default: $(PROJECT)
	$(info CPPFLAGS : $(CPPFLAGS))
	$(info CXXFLAGS : $(CXXFLAGS))
	$(info CXXFLAGS : $(CXXFLAGS))
	$(info LDFLAGS : $(LDFLAGS))
	$(info CLANGLIBS : $(CLANGLIBS))
	$(info LLVMLIBS : $(LLVMLIBS))

%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(QUIET)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(PROJECT): $(PROJECT_OBJECTS)
	@echo Linking $@
	$(QUIET)$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS)

clean:
	$(QUIET)rm -rf $(PROJECT) $(PROJECT_OBJECTS)
