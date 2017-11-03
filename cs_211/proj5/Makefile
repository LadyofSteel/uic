CC 			:= g++
SRCDIR 	:= .
SRCEXT 	:= cpp
TARGET 	:= proj5
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
HEADERS := $(shell find $(SRCDIR) -type f -name "*.h")
OBJECTS := $(SOURCES:.cpp=.o)
CFLAGS 	:= -g -Wall

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) -c $(SOURCES) $(CFLAGS)
	$(CC) -o $@ $(OBJECTS)

run:
	./$(TARGET)

debug: clean $(TARGET)
	./$(TARGET) -d

all: clean $(TARGET) run

clean:
	@echo "Cleaning..."
	$(RM) $(TARGET) $(OBJECTS)

.PHONY: clean
