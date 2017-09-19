CC 			:= gcc
SRCDIR 	:= .
SRCEXT 	:= c
TARGET 	:= proj2
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
HEADERS := $(shell find $(SRCDIR) -type f -name "*.h")
CFLAGS 	:= -g -Wall

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(SOURCES) $(CFLAGS)

run:
	./$(TARGET)

debug:
	./$(TARGET) -d

all: $(TARGET) run

clean:
	@echo "Cleaning..."
	$(RM) $(TARGET)

.PHONY: clean
