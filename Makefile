FLAGS := -std=c++11 -Wall -Wextra -pedantic
OBJ := Graph.o ATSP.o Permutation.o File.o Menu.o Edge.o EdgeList.o Heap.o

pro: main.cpp $(OBJ)
	g++ $(FLAGS) $^ -o $@

%.o: %.cpp %.h
	g++ $(FLAGS) -c $< -o $@


test: test.cpp $(OBJ)
	g++ $(FLAGS) $^ -o $@

.PHONY: clean
clean:
	rm *.o pro
