run:
	g++ -O3 -std=c++11 solver.cc -o solver.out
	./solver.out

clean:
	rm -f solver.out