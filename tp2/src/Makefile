CC = g++
CXXFLAGS = -std=c++17
CPPFLAGS = -I.
SRC := $(shell find . -type f -name '*.cpp' | sort)
OBJ := $(patsubst %.cpp,build/%.o,$(SRC))
EXEC = gap_simulator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o "$@"

build/%.o: %.cpp
	@mkdir -p "$(dir $@)"
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c "$<" -o "$@"

clean:
	rm -rf build $(EXEC)
	rm -f *.o */*.o */*/*.o