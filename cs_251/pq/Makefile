CC := g++
SOURCES := main.cpp pqueue.cpp
TARGET := pq
CFLAGS := -g -std=c++11 -Wall

build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $^

run:
	./$(TARGET)
	
clean:
	rm $(TARGET)