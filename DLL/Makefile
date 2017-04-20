run: hw4.o hw4_definitions.o
	g++ hw4.o hw4_definitions.o -o run

hw1: hw4.cpp hw4_classes.h hw4_functions.h
	g++ -c hw4.cpp

hw1_definitions.o: hw4_definitions.cpp hw4_classes.h hw4_functions.h
	g++ -c hw4_definitions.cpp

clean:
	rm *.o run

