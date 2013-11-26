#include "Deck.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Deck d;
    Card c1;
    for (int i = 0; i < 52; i++)
    {
        c1 = d.deal();
        cout << c1 << endl;
        if (i == 13) assert (c1.get_suit() == Card::HEARTS && c1.get_rank() == Card::TWO);
        if (i == 26) assert (c1.get_suit() == Card::CLUBS && c1.get_rank() == Card::TWO);
        if (i == 39) assert (c1.get_suit() == Card::DIAMONDS && c1.get_rank() == Card::TWO);
    }
    return 0;
}
