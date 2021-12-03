TARGET = ex_mutex
TARGET = test_stack_s

CPPFLAGS = -I../lib

vpath %.h ../lib

all: $(TARGET)

$(TARGET): $(TARGET).cc
	g++ -std=c++17 $(CPPFLAGS) -o $@ $^ -pthread

clean:
	rm -f $(TARGET)