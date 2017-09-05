CC := g++
SOURCES := main.cpp graph.cpp
TARGET := proj6
CFLAGS := -g -std=c++11 -Wall

build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $^

run:
	./$(TARGET)
	
clean:
	rm $(TARGET)