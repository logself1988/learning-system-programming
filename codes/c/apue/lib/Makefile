include ../common.mk

SOURCES = error.c print.c sync.c thread.c
OBJECTS = $(subst .c,.o,$(SOURCES))
LIB = libapue.a

all: $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIB) $^

clean:
	$(RM) $(OBJECTS) $(LIB)
