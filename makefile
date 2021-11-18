
sorting: sorting.o
	g++ -o main sorting.o

sorting.o: sorting.cpp
	g++ -c sorting.cpp

compile: sorting

clean:
	rm -f *.o
	rm -f *~
	rm -f main
