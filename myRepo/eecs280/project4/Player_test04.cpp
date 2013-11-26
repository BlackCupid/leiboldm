#include <iostream>
#include <cassert>
#include "Player.h"

using namespace std;
int main()
{
    Player * p = player_factory("counting");
    Hand pHand;

    Card two = Card(Card::TWO, Card::SPADES);
    Card three = Card(Card::THREE, Card::SPADES);
    Card four = Card(Card::FOUR, Card::SPADES);
    Card five = Card(Card::FIVE, Card::SPADES);
    Card six = Card(Card::SIX, Card::SPADES);
    Card seven = Card(Card::SEVEN, Card::SPADES);
    Card eight = Card(Card::EIGHT, Card::SPADES);
    Card nine = Card(Card::NINE, Card::SPADES);
    Card ace = Card(Card::ACE, Card::SPADES);
    Card ten = Card(Card::TEN, Card::SPADES);
    Card jack = Card(Card::JACK, Card::SPADES);
    Card queen = Card(Card::QUEEN, Card::SPADES);
    Card king = Card(Card::KING, Card::SPADES);

    p->shuffled();

    unsigned int bankroll = 100;
    int minimum = 5;
    // 10, J, Q, K, A decrease count by one
    // 2, 3, 4, 5, 6 increase count by one
    p->expose(two); p->expose(two); // count = 2
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->expose(ten);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(three);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->expose(jack);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(four);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->expose(queen);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(five);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->expose(king);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(six);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->expose(ace);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(seven);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(two);
    p->expose(seven);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->expose(eight);
    assert(p->bet(bankroll, minimum) == minimum*2);
    p->expose(king);
    p->expose(eight);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(nine);
    assert(p->bet(bankroll, minimum) == minimum);
    p->expose(two);
    p->expose(nine);
    assert(p->bet(bankroll, minimum) == minimum*2);
    return 0;
      


    return 0;
}
