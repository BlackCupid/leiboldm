#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
   Deck d = Deck();
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

   for( int i = 0; i < 52; i++)
   {
      Card x = d.deal();
      assert(x.get_rank() == deck[i].get_rank());
      assert(x.get_suit() == deck[i].get_suit());
   }
   cout << "Deck_test07 successful\n";
   return 0;
}
