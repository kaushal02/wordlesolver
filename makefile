run: main.cc
	g++ -O3 -std=c++11 main.cc -o main.out
	./main.out

clean:
	rm -f main.out