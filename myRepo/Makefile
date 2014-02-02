PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

FLAGS = -Wall -Wextra -pedantic -Wvla -std=c++11

release: FLAGS += -O3
release: all

debug: FLAGS += -g
debug: all

all: proj1.o Routing.o farmpoint.o
	g++ $(FLAGS) proj1.o Routing.o farmpoint.o -o proj1

proj1.o: proj1.cpp Routing.cpp
	g++ $(FLAGS) -c proj1.cpp

Routing.o: Routing.cpp
	g++ $(FLAGS) -c Routing.cpp

farmpoint.o: farmpoint.cpp
	g++ $(FLAGS) -c farmpoint.cpp

submit:
	dos2unix -U *; tar czf ./submit.tar.gz *.cpp *.h Makefile test*.txt

clean:
	rm -vf *.o proj1 submit.tar.gz
