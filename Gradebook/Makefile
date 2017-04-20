run: hw2.o hw2_definitions.o
	g++ hw2.o hw2_definitions.o -o run

hw1.o: hw2.cpp hw2_structs.h hw2_functions.h
	g++ -c hw2.cpp

hw1_definitions.o: hw2_definitions.cpp hw2_structs.h hw2_functions.h
	g++ -c hw2_definitions.cpp

clean:
	rm *.o run
