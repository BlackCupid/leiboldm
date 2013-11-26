#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Deck d1;
    d1.shuffle(1);
    Card c1, c2;
    c1 = d1.deal();
    c2 = d1.deal();
    assert (c1.get_rank() == Card::THREE && c1.get_suit() == Card::SPADES);
    assert (c2.get_rank() == Card::TWO && c2.get_suit() == Card::SPADES);
    Card c3 = d1.deal();
    assert (c3.get_rank() == Card::FOUR && c3.get_suit() == Card::SPADES);
    return 0;
}
