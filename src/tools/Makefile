all: testtarlib

testtarlib: tarlib.o testtarlib.o
	g++ -o $@ $^

tarlib.o: tarlib.cpp
	g++ -c $^

testtarlib.o: testtarlib.cpp
	g++ -c $^

clean:
	rm *.o
	rm testtarlib
