# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Wall -Werror -pedantic
LIB_SFML = -lsfml-graphics -lsfml-window -lsfml-system

# Source and object files
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# Static library and executable
STATIC_LIB = AniPlayer.a
EXE = AniPlayer

.PHONY: all clean lint

# Default build target
all: $(EXE)

# Build static library from all object files except main.o
$(STATIC_LIB): $(filter-out main.o, $(OBJ))
	ar rcs $@ $^

# Build executable by linking main.o and the static library
$(EXE): main.o $(STATIC_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB_SFML)

# Compile each .cpp to .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f *.o $(EXE) $(STATIC_LIB)

# Optional linting target
lint:
	cpplint *.cpp *.hpp

