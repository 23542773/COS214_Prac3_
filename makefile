CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g --coverage
LDFLAGS = --coverage

TARGET = petSpace
OBJS = PetSpace.o TestingMain.o

all: $(TARGET)

PetSpace.o: PetSpace.cpp PetSpace.h
	$(CXX) $(CXXFLAGS) -c PetSpace.cpp

TestingMain.o: TestingMain.cpp PetSpace.h
	$(CXX) $(CXXFLAGS) -c TestingMain.cpp

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

# Generate coverage report
coverage: clean $(TARGET) run
	gcov -b PetSpace.cpp TestingMain.cpp > coverage.txt
	@echo "Coverage report generated in coverage.txt"

clean:
	rm -rf *.o $(TARGET) *.gcda *.gcno *.gcov coverage.info coverage_report coverage.txt