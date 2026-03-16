CXX=g++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
SOURCES=Entity.cpp Resource.cpp Scene.cpp Playground.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: demo
	./demo

demo: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestRunner.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test
	./test

TestRunner.o: test.cpp Entity.hpp Resource.hpp Scene.hpp SmartStack.hpp Playground.hpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

Entity.o: Entity.cpp Entity.hpp

Resource.o: Resource.cpp Resource.hpp

Scene.o: Scene.cpp Scene.hpp Entity.hpp Resource.hpp

Playground.o: Playground.cpp Playground.hpp Entity.hpp Resource.hpp Scene.hpp SmartStack.hpp

main.o: main.cpp Entity.hpp Resource.hpp Scene.hpp SmartStack.hpp Playground.hpp

clean:
	rm -f *.o demo test