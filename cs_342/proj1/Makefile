JC 			:= javac
SRCDIR 	:= .
SRCEXT 	:= java
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
JFLAGS 	:= -g
TARGET 	:= Game

build: $(SOURCES)
	$(JC) $(JFLAGS) $(SOURCES)

run:
	java $(TARGET)

all: build run

clean:
	@echo "Cleaning..."
	$(RM) *.class

.PHONY: clean
