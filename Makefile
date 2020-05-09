all: compile

compile: main.o logger.o map.o spawner.o creep.o entity.o
	g++ main.o logger.o map.o spawner.o creep.o entity.o -o main --std=c++11 -lpthread

main.o: main.cpp
	g++ -c main.cpp --std=c++11

logger.o: src/logger.cpp
	g++ -c src/logger.cpp --std=c++11

map.o: src/map.cpp
	g++ -c src/map.cpp --std=c++11 -lpthread

spawner.o: src/spawner.cpp
	g++ -c src/spawner.cpp --std=c++11 -lpthread

creep.o: src/creep.cpp
	g++ -c src/creep.cpp --std=c++11 -lpthread

entity.o: src/entity.cpp
	g++ -c src/entity.cpp --std=c++11

clean:
	rm *.o logs/*.log