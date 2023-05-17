a.out: main.o questions.h volley.h  
	g++-10 -g -std=c++2a main.cc -lgtest -pthread

main.o: main.cc questions.h volley.h 
	g++-10 -g -std=c++2a main.cc -lgtest -pthread

clean:
	rm -f a.out core *.o
