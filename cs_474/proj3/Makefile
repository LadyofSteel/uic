CC 			:= g++
SRCDIR 	:= .
SRCEXT 	:= cpp
TARGET 	:= proj3
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
HEADERS := $(shell find $(SRCDIR) -type f -name "*.h")
CFLAGS 	:= -g -Wall -std=c++11

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(SOURCES) $(CFLAGS)

run:
	./$(TARGET)

all: clean $(TARGET) run

clean:
	@echo "Cleaning..."
	$(RM) $(TARGET)

.PHONY: clean
