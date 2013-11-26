#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Deck d;
    int cards;
    for (int i = 52; i > 0; i--)
    {
        cards = d.cards_remaining();
        assert (cards == i);
        d.deal();
    }
    cards = d.cards_remaining();
    assert(cards == 0);
  
    return 0;

}
