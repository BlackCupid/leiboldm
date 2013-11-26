#include <iostream>
#include <cassert>
#include "Player.h"

using namespace std;
int main()
{
    Player * p = player_factory("counting");
    unsigned int Minimum = 0;
    unsigned int bankroll = 0;
    Card high = Card(Card::JACK, Card::SPADES);
    Card low = Card(Card::TWO, Card::SPADES);
    assert(p->bet(bankroll, Minimum) == 0);
    bankroll = 8;
    assert(p->bet(bankroll, Minimum) == 0);

    //count = 2
    p->expose(low); p->expose(low);
    assert(p->bet(bankroll, Minimum) == 0);
    Minimum = 1;
    assert(p->bet(bankroll, Minimum) == 2);
    Minimum = 5;
    assert(p->bet(bankroll, Minimum) == 8);
    bankroll = 10;
    assert(p->bet(bankroll, Minimum) == 10);
    Minimum = 10;
    assert(p->bet(bankroll, Minimum) == 10);   

    //count = 1
    p->expose(high);
    assert(p->bet(bankroll, Minimum) == 10);
    Minimum = 8;
    assert(p->bet(bankroll, Minimum) == 8);
    return 0;
}
