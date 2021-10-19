program := player
sources := player.c
libraries := -ldb -lcodec -lui

lib_dirs := ../../lib/codec ../../lib/db ../../lib/ui
vpath %.a $(lib_dirs)

all: $(program)

include ../../common.mk

$(program): $(objects) $(libraries)
