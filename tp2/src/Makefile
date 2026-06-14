CC = g++
CXXFLAGS = -std=c++17
CPPFLAGS = -I.
SRC := $(shell find . -type f -name '*.cpp' ! -path './tests/*' | sort)
OBJ := $(patsubst %.cpp,build/%.o,$(SRC))
EXEC = gap_simulator
TEST_EXEC = tests/test_solucion

.PHONY: all tests clean

all: $(EXEC)

tests:
	$(MAKE) $(TEST_EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o "$@"

$(TEST_EXEC): tests/test_solucion.cpp instance.cpp solucion.cpp
	@mkdir -p tests
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $^ -o "$@"

build/%.o: %.cpp
	@mkdir -p "$(dir $@)"
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c "$<" -o "$@"

clean:
	rm -rf build $(EXEC) $(TEST_EXEC)
	rm -f *.o */*.o */*/*.o