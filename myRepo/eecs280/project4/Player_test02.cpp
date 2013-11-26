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
    Card nine = Card(Card::NINE, Card::SPADES);
    Card ace = Card(Card::ACE, Card::SPADES);
     
    // Always hit if value <= 11
    pHand.add_card(nine);
    assert(p->draw(nine, pHand));
    pHand.add_card(two);
    assert(p->draw(nine, pHand));
    assert(p->draw(four, pHand));
    assert(p->draw(five, pHand));
    assert(p->draw(six, pHand));
    assert(p->draw(seven, pHand));
    assert(p->draw(two, pHand));

    // hit if value between 13 and 16 and dealer's card isn't 2-6
    pHand.add_card(two);
    assert(p->draw(nine, pHand));
    assert(!p->draw(two, pHand));
    assert(!p->draw(six, pHand));
    pHand.add_card(three); // value now = 16
    assert(!p->draw(two, pHand));
    assert(!p->draw(six, pHand));
    assert(p->draw(nine, pHand));
    assert(p->draw(ace, pHand));

    // stand if value 17 or greater
    pHand.add_card(two); // value now = 18
    assert(!p->draw(nine, pHand));
    pHand.discard_all();
    pHand.add_card(nine);
    pHand.add_card(four);
    pHand.add_card(four); // value now = 17
    assert(!p->draw(nine, pHand));
    pHand.add_card(nine);
    assert(!p->draw(nine, pHand));

    // value = 12, only stands if dealer = 4,5,or 6
    pHand.discard_all();
    pHand.add_card(four); pHand.add_card(four); pHand.add_card(four);
    assert(!p->draw(four, pHand));
    assert(!p->draw(five, pHand));
    assert(!p->draw(six, pHand));
    assert(p->draw(two, pHand));
    assert(p->draw(nine, pHand));

    return 0;

}

