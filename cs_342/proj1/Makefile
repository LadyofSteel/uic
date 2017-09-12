JC 						:= javac
SRCDIR 				:= .
SRCEXT 				:= java
SOURCES 			:= $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)" | grep -vG "Test*")
JFLAGS 				:= -g
TARGET 				:= Game
TESTS 				:= $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
TEST_TARGETS 	:= TestCard TestCardPile

build: $(SOURCES)
	$(JC) $(JFLAGS) $(SOURCES)

run:
	java $(TARGET)

all: build run

tests: $(TESTS)
	javac -cp /usr/share/java/junit4.jar $(TESTS)

runtests:
	java -cp /usr/share/java/junit4.jar:. org.junit.runner.JUnitCore $(TEST_TARGETS)

clean:
	@echo "Cleaning..."
	$(RM) *.class

.PHONY: clean
