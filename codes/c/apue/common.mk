CFLAGS = -Wall -g -static 
#CFLAGS = -g -O
CPPFLAGS = -I../include
ARFLAGS = rv
RM = rm -rf *.dSYM
LDFLAGS = 
# put library link after source code
LDLIBS = -L../lib -lapue

vpath %.h ../include
