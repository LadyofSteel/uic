CC 			:= g++
SRCDIR 	:= .
SRCEXT 	:= cpp
TARGET 	:= proj3
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
CFLAGS 	:= -g -Wall

$(TARGET): $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(CFLAGS)

run:
	./$(TARGET)

clean:
	@echo "Cleaning..."
	$(RM) $(TARGET)

.PHONY: clean
