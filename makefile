run: main.cc
	g++ -O3 -std=c++11 main.cc -o main.out
	./main.out

test: main.cc
	g++ -O3 -std=c++11 main.cc -o main.out
	./main.out benchmark

clean:
	rm -f main.out