PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT_LOGS = $(PROJECT_ROOT)logs
PROJECT_SRC = $(PROJECT_ROOT)src
PROJECT_BUILD = $(PROJECT_ROOT)build/bin

CXX = --std=c++11
LPT = -lpthread
CXXFLAGS = $(CXX) $(LPT)
GCC = g++
BUILD_MODE = run

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else
	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all: compile clean

compile: main.o logger.o map.o entity.o creep.o
	$(GCC) main.o logger.o map.o entity.o creep.o -o $(PROJECT_BUILD)/game $(CXXFLAGS)

main.o:
	$(GCC) -c $(PROJECT_ROOT)/main.cpp $(CXXFLAGS) 

map.o:
	$(GCC) -c $(PROJECT_SRC)/map.cpp $(CXXFLAGS) 

entity.o:
	$(GCC) -c $(PROJECT_SRC)/entity.cpp $(CXXFLAGS)

creep.o:
	$(GCC) -c $(PROJECT_SRC)/creep.cpp $(CXXFLAGS)  

logger.o:
	$(GCC) -c $(PROJECT_SRC)/logger.cpp $(CXXFLAGS)

clean:
	rm -rf *.o
	
clear:
	rm -rf $(PROJECT_LOGS)/*.log
	
	