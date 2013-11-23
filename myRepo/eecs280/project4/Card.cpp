#include <iostream>
#include <string>
#include "Card.h"
using namespace std;


std::ostream& operator<< (std::ostream& os, const Card& c)
{ 
   const int NUMRANKS = 13;
   Card::Rank ranks[NUMRANKS] = {Card::TWO, Card::THREE, Card::FOUR,
     Card::FIVE, Card::SIX, Card::SEVEN, Card::EIGHT, Card::NINE, 
     Card::TEN, Card:: JACK, Card::QUEEN, Card::KING, Card::ACE};
   string rankStrings[NUMRANKS] = {"Two", "Three", "Four", "Five", "Six",
                "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King",
                "Ace"};
   for (int i = 0; i < NUMRANKS; i++){
      if (c.get_rank() == ranks[i]){
         os << rankStrings[i];
         break;
      }
   } 
   os << " of ";
   const int NUMSUITS = 4;
   Card::Suit suits[NUMSUITS] = {Card::SPADES, Card::HEARTS,
                                Card:: CLUBS, Card::DIAMONDS};
   string suitStrings[NUMSUITS] = {"Spades", "Hearts", "Clubs", "Diamonds"};
   for (int i = 0; i < NUMSUITS; i++){
      if (c.get_suit() == suits[i]){
         os << suitStrings[i];
         break;
      }
   }
   return os;
}

Card::Card() : rank(TWO), suit(SPADES) {}

Card::Card(Rank rank_in, Suit suit_in)
   : rank(rank_in), suit(suit_in) {}

Card::Rank Card::get_rank() const
{
    return rank;
}

Card::Suit Card::get_suit() const
{
    return suit;
}
