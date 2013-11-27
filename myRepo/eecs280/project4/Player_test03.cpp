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

    // if 17 or less and count is hard, always hit
    pHand.add_card(ace);
    assert(p->draw(ace, pHand));
    assert(p->draw(two, pHand));
    assert(p->draw(jack, pHand));
    pHand.add_card(six);
    assert(p->draw(ace, pHand));
    assert(p->draw(jack, pHand));
    assert(p->draw(two, pHand));

    // if 18, stand if dealer shows 2, 7, or 8.  else hit
    pHand.discard_all();
    pHand.add_card(ace);
    pHand.add_card(seven);
    assert(!p->draw(two, pHand));
    assert(!p->draw(seven, pHand));
    assert(!p->draw(eight, pHand));
    assert(p->draw(three, pHand));
    assert(p->draw(jack, pHand));
    assert(p->draw(nine, pHand));
    assert(p->draw(six, pHand));

    // if greater than 19, always stand
    pHand.discard_all();
    pHand.add_card(ace);
    pHand.add_card(eight);
    assert(!p->draw(three, pHand));
    assert(!p->draw(jack, pHand));
    assert(!p->draw(nine, pHand));
    assert(!p->draw(six, pHand));
    assert(!p->draw(ace, pHand));
    pHand.add_card(two);
    assert(!p->draw(ace, pHand));
    assert(!p->draw(two, pHand));
    assert(!p->draw(ten, pHand));
    assert(!p->draw(four, pHand));
    assert(!p->draw(five, pHand));
    return 0;    
}
