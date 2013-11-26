#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Deck d1, d2, d3;
    Card c1, c2, c3;
    d2.shuffle(0);
    d3.shuffle(52);
    for (int i = 0; i < 52; i++)
    {
        c1 = d1.deal();
        c2 = d2.deal();
        c3 = d3.deal();
        assert (c1.get_suit() == c2.get_suit() && c1.get_rank() == c2.get_rank());
        assert (c2.get_suit() == c3.get_suit() && c2.get_rank() == c3.get_rank());
    }
    return 0;
}
