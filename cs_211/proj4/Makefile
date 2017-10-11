CC 			:= gcc
SRCDIR 	:= .
SRCEXT 	:= c
TARGET 	:= proj4
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
HEADERS := $(shell find $(SRCDIR) -type f -name "*.h")
OBJECTS := $(SOURCES:.c=.o)
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
