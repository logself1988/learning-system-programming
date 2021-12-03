TARGET = hello_world

all: $(TARGET)

$(TARGET): $(TARGET).cc
	g++ -std=c++17 -o $@ $^ -pthread

clean:
	rm -f $(TARGET)