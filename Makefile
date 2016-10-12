FLAGS := -std=c++11 -Wall -Wextra -pedantic
OBJ := Graph.o Item.o ATSP.o Permutation.o FileSupport.o Menu.o

pro: main.cpp $(OBJ)
	g++ $(FLAGS) $^ -o $@

%.o: %.cpp %.h
	g++ $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm *.o pro
