CC     := g++
CFLAGS := -Wall -Werror -pedantic -O1

submit : Card.cpp Deck.cpp Player.cpp Hand.cpp blackjack.cpp Deck_test.overview Deck_test[0-9][0-9].cpp Player_test.overview Player_test[0-9][0-9].cpp
	/afs/umich.edu/class/eecs280/submit280 4 Card.cpp Deck.cpp Player.cpp Hand.cpp blackjack.cpp Deck_test.overview Deck_test[0-9][0-9].cpp Player_test.overview Player_test[0-9][0-9].cpp

Card_test00 : Card_test00.cpp Card.cpp
	$(CC) $(CFLAGS) Card_test00.cpp Card.cpp -o Card_test00

Deck_test00 : Deck_test00.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test00.cpp Deck.cpp Card.cpp -o Deck_test00

Deck_test01 : Deck_test01.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test01.cpp Deck.cpp Card.cpp -o Deck_test01

Dt02 : Deck_test02.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test02.cpp Deck.cpp Card.cpp -o dt02
	./dt02
	
Dt03 : Deck_test03.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test03.cpp Deck.cpp Card.cpp -o dt03
	./dt03
	
Dt04 : Deck_test04.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test04.cpp Deck.cpp Card.cpp -o dt04
	./dt04

Dt05 : Deck_test05.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test05.cpp Deck.cpp Card.cpp -o dt05
	./dt05

Dt06 : Deck_test06.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test06.cpp Deck.cpp Card.cpp -o dt06
	./dt06
	
Dt07 : Deck_test07.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test07.cpp Deck.cpp Card.cpp -o dt07
	./dt07
	
Dt08 : Deck_test08.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test08.cpp Deck.cpp Card.cpp -o dt08
	./dt08

Dt09 : Deck_test09.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test09.cpp Deck.cpp Card.cpp -o dt09
	./dt09

Player_test00 : Player_test00.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test00.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test00
	./Player_test00

Player_test01 : Player_test01.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test01.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test01
	./Player_test01

Player_test02 : Player_test02.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test02.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test02
	./Player_test02

Player_test03 : Player_test03.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test03.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test03
	./Player_test03
	
Player_test04 : Player_test04.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test04.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test04
	./Player_test04

Player_test05 : Player_test05.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test05.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test05
	./Player_test05
	
Player_test06 : Player_test06.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test06.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test06
	./Player_test06

blackjack :  Card.cpp rand.cpp Hand.cpp Deck.cpp Player.cpp blackjack.cpp
	$(CC) $(CFLAGS) Card.cpp rand.cpp Hand.cpp Deck.cpp Player.cpp blackjack.cpp -o blackjack

test : blackjack Card_test00 Deck_test00 Player_test00
	./Card_test00
	./Deck_test00
	./Player_test00
	./blackjack 100 3 simple > blackjack.out
	diff -q blackjack_test00.out.correct blackjack.out

clean :
	rm -vf blackjack *.out \
         Card_test[0-9][0-9] \
         Deck_test[0-9][0-9] \
         Player_test[0-9][0-9] \
		 dt[0-9][0-9]
