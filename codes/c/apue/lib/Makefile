include ../common.mk

vpath %.h ../include

SOURCES = error.c
OBJECTS = $(subst .c,.o,$(SOURCES))
LIB = libapue.a

all: $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIB) $^

clean:
	$(RM) $(OBJECTS) $(LIB)
