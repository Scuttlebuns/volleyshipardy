a.out: main.o questions.h volley.h games.h
	g++ -g -Og main.cc -lgtest -pthread

main.o: main.cc questions.h volley.h games.h
	g++ -g -Og main.cc -lgtest -pthread

clean:
	rm -f a.out core *.o
