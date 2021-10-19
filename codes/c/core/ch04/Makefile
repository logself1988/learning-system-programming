include ../common.mk

TARGET = find_ould calc cpp

all: $(TARGET)

calc: main.c getop.c getch.c stack.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET)