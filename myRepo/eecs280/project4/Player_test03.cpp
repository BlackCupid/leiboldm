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

// construct deck of all 52 cards
    Card deck[52];
    const int NUMSUITS = 4;
    const int NUMRANKS = 13;
    for (int i = 0; i < NUMSUITS; i++)
    {
       for (int j = 0; j < NUMRANKS; j++)
       {
          Card::Rank ranks[NUMRANKS] = {Card::TWO, Card::THREE, Card::FOUR,
             Card::FIVE, Card::SIX, Card::SEVEN, Card::EIGHT, Card::NINE, 
             Card::TEN, Card:: JACK, Card::QUEEN, Card::KING, Card::ACE};
          if (i == 0) deck[NUMRANKS*i + j] = Card(ranks[j], Card::SPADES);
          if (i == 1) deck[NUMRANKS*i + j] = Card(ranks[j], Card::HEARTS); 
          if (i == 2) deck[NUMRANKS*i + j] = Card(ranks[j], Card::CLUBS);
          if (i == 3) deck[NUMRANKS*i + j] = Card(ranks[j], Card::DIAMONDS);
       }
    }

    // if 17 or less and count is soft, always hit
    pHand.add_card(ace);
    assert(p->draw(ace, pHand));
    assert(p->draw(two, pHand));
    assert(p->draw(jack, pHand));
    pHand.add_card(six);
    assert(p->draw(ace, pHand));
    assert(p->draw(jack, pHand));
    assert(p->draw(two, pHand));
    for (int i = 0; i < 52; i++)
    {
       assert(p->draw(deck[i], pHand));
    }

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
    for (int i = 0; i < 52; i++)
    {
       assert(!p->draw(deck[i], pHand));
    }
    pHand.add_card(two);
    assert(!p->draw(ace, pHand));
    assert(!p->draw(two, pHand));
    assert(!p->draw(ten, pHand));
    assert(!p->draw(four, pHand));
    assert(!p->draw(five, pHand));

    pHand.discard_all();
    pHand.add_card(ace);
    pHand.add_card(nine);
    for (int i = 0; i < 52; i++)
    {
       assert(!p->draw(deck[i], pHand));
    }
    return 0;    
}
