#include <iostream>
#include <cassert>
#include "Player.h"

using namespace std;
int main()
{
    Player * p = player_factory("counting");
    Hand pHand;

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
    Card two = Card(Card::TWO, Card::SPADES);
    Card three = Card(Card::THREE, Card::SPADES);
    Card four = Card(Card::FOUR, Card::SPADES);
    Card five = Card(Card::FIVE, Card::SPADES);
    Card six = Card(Card::SIX, Card::SPADES);
    Card seven = Card(Card::SEVEN, Card::SPADES);
    Card eight = Card(Card::EIGHT, Card::SPADES);
    Card nine = Card(Card::NINE, Card::SPADES);
    Card ten = Card(Card::TEN, Card::SPADES);
    Card ace = Card(Card::ACE, Card::SPADES);
     
    // Always hit if value <= 11
    pHand.add_card(nine);
    for (int i = 0; i < 52; i++)
    {
        assert(p->draw(deck[i], pHand));
    }
    pHand.add_card(two);
    for (int i = 0; i < 52; i++)
    {
        assert(p->draw(deck[i], pHand));
    } 

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
    pHand.discard_all();
    pHand.add_card(ace);
    pHand.add_card(six);
    pHand.add_card(nine);
    assert(p->draw(ace, pHand));
    assert(p->draw(nine, pHand));
    assert(!p->draw(two, pHand));
    assert(!p->draw(six, pHand));
    assert(p->draw(seven, pHand));

    pHand.discard_all();
    pHand.add_card(ace);
    pHand.add_card(two);
    pHand.add_card(ten); //value = 13, hand is hard
    assert(p->draw(ace, pHand));
    assert(!p->draw(two, pHand));
    assert(!p->draw(five, pHand));
    assert(!p->draw(six, pHand));
    assert(p->draw(seven, pHand));

    // stand if value 17 or greater
    pHand.add_card(four); // value now = 18
    for (int i = 0; i < 52; i++)
    {
        assert(!p->draw(deck[i], pHand));
    }
    pHand.discard_all();
    pHand.add_card(nine);
    pHand.add_card(four);
    pHand.add_card(four); // value now = 17
    for (int i = 0; i < 52; i++)
    {
        assert(!p->draw(deck[i], pHand));
    }
    pHand.add_card(nine);
    assert(!p->draw(nine, pHand));

    pHand.discard_all();
    pHand.add_card(ten);
    pHand.add_card(ten);
    pHand.add_card(ace); // value now 21
    for (int i = 0; i < 52; i++)
    {
       assert(!p->draw(deck[i], pHand));
    }

    // value = 12, only stands if dealer = 4,5,or 6
    pHand.discard_all();
    pHand.add_card(four); pHand.add_card(four); pHand.add_card(four);
    assert(!p->draw(four, pHand));
    assert(!p->draw(five, pHand));
    assert(!p->draw(six, pHand));
    assert(p->draw(two, pHand));
    assert(p->draw(nine, pHand));
    pHand.discard_all();
    pHand.add_card(ace);
    pHand.add_card(ace); // value = 12, hand is soft
    for (int i = 0; i < 52; i++)
    {
       assert(p->draw(deck[i], pHand));
    }
    pHand.add_card(ten); // value = 12, hand is hard
    assert(!p->draw(four, pHand));
    assert(!p->draw(five, pHand));
    assert(!p->draw(six, pHand));
    assert(p->draw(three, pHand));
    assert(p->draw(seven, pHand));
    assert(p->draw(ace, pHand));
    assert(p->draw(two, pHand));
    assert(p->draw(nine, pHand));
 
    return 0;

}

