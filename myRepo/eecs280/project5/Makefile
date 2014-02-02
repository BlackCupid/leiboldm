CC = g++
CFLAGS = -ansi -pedantic -Werror -Wall -O1

calc: calc.cpp
	$(CC) $(CFLAGS) calc.cpp -o calc

calctest: calc.cpp
	$(CC) $(CFLAGS) calc.cpp -o calc
	./calc < calc.in > calc.out
	diff calc.out calc.out.correct

call: call.cpp
	$(CC) $(CFLAGS) call.cpp -o call

calltest: call.cpp
	$(CC) $(CFLAGS) call.cpp -o call
	./call < call.in > call.out
	diff call.out call.out.correct

submit:
	/afs/umich.edu/class/eecs280/submit280 5 call.cpp calc.cpp dlist.h

dlisttest: dlist_test.cpp
	$(CC) $(CFLAGS) dlist_test.cpp -o dlist_test
	./dlist_test

dlisttest2: dlist_test2.cpp
	$(CC) $(CFLAGS) dlist_test2.cpp -o dlist_test2
	./dlist_test2

dlisttest3: dlist_test3.cpp
	$(CC) $(CFLAGS) dlist_test3.cpp -o dlist_test3
	./dlist_test3

clean:
	rm dlist_test3
	rm dlist_test2
	rm dlist_test
