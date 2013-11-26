#include <iostream>
#include <cassert>
#include "Player.h"

using namespace std;
int main()
{
    Player * p = player_factory("counting");
    Hand pHand;

    Card two = Card(Card::TWO, Card::SPADES);

    int minimum = 5;
    int bankroll = 100;

    p->expose(two);
    p->expose(two);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->shuffled();
    assert(p->bet(bankroll, minimum) == minimum);


    return 0;
}
