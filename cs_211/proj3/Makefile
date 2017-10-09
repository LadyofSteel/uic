CC 			:= gcc
SRCDIR 	:= .
SRCEXT 	:= c
TARGET 	:= proj3
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
HEADERS := $(shell find $(SRCDIR) -type f -name "*.h")
CFLAGS 	:= -g -Wall

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(SOURCES) $(CFLAGS)

run:
	./$(TARGET) input1.txt

debug: clean $(TARGET)
	./$(TARGET) -d input1.txt

all: clean $(TARGET) run

clean:
	@echo "Cleaning..."
	$(RM) $(TARGET)

.PHONY: clean
