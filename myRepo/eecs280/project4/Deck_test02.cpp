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
        if (i/13 == 1) assert (c1.get_suit() == Card::HEARTS);
        if (i/13 == 2) assert (c1.get_suit() == Card::CLUBS);
        if (i/13 == 3) assert (c1.get_suit() == Card::DIAMONDS);
    }
    return 0;
}
