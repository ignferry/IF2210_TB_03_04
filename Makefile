TC_FOLDER = tests
SRC_FOLDER = src
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
ALL_SRCS := $(wildcard ./$(SRC_FOLDER)/*.cpp)

all: compile test check

# Compile all cpp files except check.cpp
compile:
	g++ -std=c++17 main.cpp $(ALL_SRCS) -o $(EXECUTABLE_FILENAME)

run:
	./main
# Test
test: $(TC_FOLDER)/*.$(EXT_IN)
	for inputfile in $(TC_FOLDER)/*.$(EXT_IN); do \
		./$(EXECUTABLE_FILENAME) < $$inputfile; \
	done;

# Check
check: FORCE check.cpp
	g++ -std=c++17 -o check check.cpp
	./check

FORCE: ;