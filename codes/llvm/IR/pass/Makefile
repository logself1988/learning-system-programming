LLVM_CONFIG?=llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra -fPIC
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

LOADABLE_MODULE_OPTIONS=-shared -Wl,-O1

FNARGPASS=fnarg.so
FNARGPASS_OBJECTS=FnArgCnt.o

default: $(FNARGPASS)
	$(info CPPFLAGS : $(CPPFLAGS))
	$(info CXXFLAGS : $(CXXFLAGS))
	$(info CXXFLAGS : $(CXXFLAGS))
	$(info LDFLAGS : $(LDFLAGS))

%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $*.cpp
	$(QUIET)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(FNARGPASS): $(FNARGPASS_OBJECTS)
	@echo Linking $@
	$(QUIET)$(CXX) -o $@ $(LOADABLE_MODULE_OPTIONS) $(CXXFLAGS) $(LDFLAGS) $^

clean:
	$(QUIET)rm -rf $(FNARGPASS) $(FNARGPASS_OBJECTS)
