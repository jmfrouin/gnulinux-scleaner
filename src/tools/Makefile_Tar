all: testtar

testtar: tar_archive.o testtar.o
	g++ -o $@ $^

tar_archive.o: tar_archive.cpp
	g++ -c $^

testtar.o: testtar.cpp
	g++ -c $^

clean:
	rm *.o
	rm -f testtar
