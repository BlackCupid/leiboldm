#include <iostream>
#include <cassert>
#include "Player.h"

using namespace std;
int main()
{
    Player * p = player_factory("counting");
    Hand pHand;

    Card two = Card(Card::TWO, Card::SPADES);
    Card ten = Card(Card::TEN, Card::SPADES);

    int minimum = 5;
    int bankroll = 100;

    p->expose(two);
    p->expose(two);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->shuffled();
    assert(p->bet(bankroll, minimum) == minimum);
    for (int i = 0; i < 1000; i++)
    {
        p->expose(two);
    }
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->shuffled();
    assert(p->bet(bankroll, minimum) == minimum);
    for (int i = 0; i < 1000; i++)
    {
        p->expose(ten);
    }
    assert(p->bet(bankroll, minimum) == minimum);
    p->shuffled();
    assert(p->bet(bankroll, minimum) == minimum);


    return 0;
}
