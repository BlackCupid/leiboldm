CC     := g++
CFLAGS := -Wall -Werror -pedantic -O1

Card_test00 : Card_test00.cpp Card.cpp
	$(CC) $(CFLAGS) Card_test00.cpp Card.cpp -o Card_test00

Deck_test00 : Deck_test00.cpp Deck.cpp Card.cpp
	$(CC) $(CFLAGS) Deck_test00.cpp Deck.cpp Card.cpp -o Deck_test00

Player_test00 : Player_test00.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp
	$(CC) $(CFLAGS) Player_test00.cpp Card.cpp Hand.cpp Deck.cpp Player.cpp rand.cpp -o Player_test00

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
         Player_test[0-9][0-9]
