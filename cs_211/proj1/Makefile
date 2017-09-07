CC 			:= gcc
SRCDIR 	:= .
SRCEXT 	:= c
TARGET 	:= proj1
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
CFLAGS 	:= -g -Wall

$(TARGET): $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(CFLAGS)

run:
	./$(TARGET)

all: $(TARGET) run

clean:
	@echo "Cleaning..."
	$(RM) $(TARGET)

.PHONY: clean
