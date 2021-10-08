local_program := $(subdirectory)/player
local_src := $(addprefix $(subdirectory)/,$(wildcard *.c))
local_objs := $(subst .c,.o,$(local_src))

programs += $(local_program)
sources += $(local_src)

$(local_program): $(local_objs) $(libraries)
