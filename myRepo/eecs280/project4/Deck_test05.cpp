#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Deck d;
    d.deal(); d.deal(); d.deal();
    d.shuffle(26);
    d.shuffle(1);
    Card c;
    c = d.deal();
    assert(c.get_rank() == Card::TWO && c.get_suit() == Card::SPADES);
    c = d.deal();
    assert(c.get_rank() == Card::TWO && c.get_suit() == Card::CLUBS);
    return 0;
}
