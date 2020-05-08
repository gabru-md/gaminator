all: compile

compile: main.o logger.o map.o creep.o entity.o
	g++ main.o logger.o map.o creep.o entity.o -o main

main.o: main.cpp
	g++ -c main.cpp

logger.o: src/logger.cpp
	g++ -c src/logger.cpp

map.o: src/map.cpp
	g++ -c src/map.cpp

creep.o: src/creep.cpp
	g++ -c src/creep.cpp

entity.o: src/entity.cpp
	g++ -c src/entity.cpp

clean:
	rm *.o logs/*