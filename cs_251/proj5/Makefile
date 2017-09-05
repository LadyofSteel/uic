CC := gcc 
SOURCES := main.c ht.c
TARGET := proj5
CFLAGS := -g -std=c99 -Wall

build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $^

run:
	./$(TARGET)
	
clean:
	rm $(TARGET)